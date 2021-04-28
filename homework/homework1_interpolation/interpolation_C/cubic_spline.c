#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cubic_spline.h"

cubic_spline * cubic_spline_alloc (int n, double x[], double y[])
{
	cubic_spline * spline = (cubic_spline *) malloc (sizeof (cubic_spline)); 

	spline->n = n; 

	spline->x = (double *) malloc (n*sizeof (double)); 
	spline->y = (double *) malloc (n*sizeof (double)); 

	for (int i = 0; i < n; i++) 
	{
		spline->x[i] = x[i]; 
		spline->y[i] = y[i]; 
	}

	double h[n - 1], p[n - 1]; 

	for (int i = 0; i < n - 1; i++)
	{
		h[i] = x[i + 1] - x[i]; 
		assert (h[i] > 0); 

		p[i] = (y[i + 1] - y[i])/h[i]; 
	}

	// Tridiagonal system
	double D[n]; D[0] = 2; D[n - 1] = 2; 
	double Q[n - 1]; Q[0] = 1; 
       	double B[n]; B[0] = 3*p[0]; B[n - 1] = 3*p[n - 2]; 
	
	for (int i = 0; i < n - 2; i++)
	{
		D[i + 1] = 2*h[i]/h[i + 1] + 2; 
		Q[i + 1] = h[i]/h[i + 1]; 
		B[i + 1] = 3*(p[i] + p[i + 1]*h[i]/h[i + 1]); 
	}

	// Gauss elimination
	for (int i = 1; i < n; i++)
	{
		D[i] -= Q[i - 1]/D[i - 1]; 
		B[i] -= B[i - 1]/D[i - 1]; 
	}

	// Back-substitution
	spline->b = (double *) malloc (n*sizeof (double)); spline->b[n - 1] = B[n - 1]/D[n - 1]; 
	spline->c = (double *) malloc ((n - 1)*sizeof (double)); 
	spline->d = (double *) malloc ((n - 1)*sizeof (double)); 

	for (int i = n - 2; i >= 0; i--)
	{
		spline->b[i] = (B[i] - Q[i]*spline->b[i + 1])/D[i];
	}

	for (int i = 0; i < n - 1; i++)
	{
		spline->c[i] = (-2*spline->b[i] - spline->b[i + 1] + 3*p[i])/h[i]; 
		spline->d[i] = (spline->b[i] + spline->b[i + 1] - 2*p[i])/h[i]/h[i];
	}

	return spline;
}

int check_and_search (cubic_spline * spline, double z)
{
	assert (z >= spline->x[0] && z <= spline->x[spline->n - 1]);
	
	int i = 0, j = spline->n - 1;

	while (j - i > 1)
	{
		int m = (i + j)/2;

		if (z > spline->x[m])
		{
			i = m;
		}
		else
		{
			j = m;
		}
	}
	return i;
}

double cubic_spline_eval (cubic_spline * spline, double z)
{
	int i = check_and_search (spline, z);
	double h = z - spline->x[i];

	return spline->y[i] + h*(spline->b[i] + h*(spline->c[i] + h*spline->d[i]));
}

double cubic_spline_integ (cubic_spline * spline, double z)
{
	int i = check_and_search (spline, z);

	double anti_derivative (int i, double z)
	{
		double h = z - spline->x[i]; 
        	
		return h*(spline->y[i] + h*(spline->b[i]/2 + h*(spline->c[i]/3 + h*spline->d[i]/4)));
	}

	double integral = anti_derivative (i, z) - anti_derivative (i, spline->x[i]); 

	while (i > 0)
	{
		i--;
		integral += anti_derivative (i, spline->x[i + 1]) - anti_derivative (i, spline->x[i]);
	}

	return integral; 
}


double cubic_spline_deriv (cubic_spline * spline, double z)
{
	int i = check_and_search (spline, z);
	double h = z - spline->x[i];

	return spline->b[i] + h*(2.*spline->c[i] + h*3.*spline->d[i]);
}

void cubic_spline_free (cubic_spline * spline)
{
	free (spline->x);
	free (spline->y);

	free (spline->b);
	free (spline->c);
	free (spline->d);

	free (spline);
}
