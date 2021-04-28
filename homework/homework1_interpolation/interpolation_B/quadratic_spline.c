#include <stdlib.h>
#include <assert.h>
#include "quadratic_spline.h"

quadratic_spline * quadratic_spline_alloc (int n, double x[], double y[])
{
	quadratic_spline * spline = (quadratic_spline *) malloc (sizeof (quadratic_spline));

	spline->n = n; 
	
	spline->x = (double *) malloc (n*sizeof (double)); 
	spline->y = (double *) malloc (n*sizeof (double)); 
	
	for (int i = 0; i < n; i++)
	{
		spline->x[i] = x[i]; 
		spline->y[i] = y[i];
	}

	double h[n - 1];
	double p[n - 1];

	for (int i = 0; i < n - 1; i++)
	{
		h[i] = x[i + 1] - x[i];
		assert (h[i] > 0);
	
		p[i] = (y[i + 1] - y[i])/h[i]; 
	}

	spline->c = (double *) malloc ((n - 1)*sizeof (double)); 
	spline->c[0] = 0; 

	for (int i = 0; i < n - 2; i++)
	{
		spline->c[i + 1] = (p[i + 1] - p[i] - spline->c[i]*h[i])/h[i + 1];
	}

	spline->c[n - 2] /= 2; 

	for (int i = n - 3; i >= 0; i--)
	{
		spline->c[i] = (p[i + 1] - p[i] - spline->c[i + 1]*h[i + 1])/h[i]; 
	}	

	spline->b = (double *) malloc ((n - 1)*sizeof (double));

	for (int i = 0; i < n - 1; i++)
	{
		spline->b[i] = p[i] - spline->c[i]*h[i]; 
	}	

	return spline; 
}

int check_and_search (quadratic_spline * spline, double z)
{
	assert( z >= spline->x[0] && spline->x[spline->n - 1]);

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

double quadratic_spline_eval (quadratic_spline * spline, double z)
{
	int i = check_and_search (spline, z);
	double h = z - spline->x[i]; 
	
	return spline->y[i] + h*(spline->b[i] + h*spline->c[i]);
}

double quadratic_spline_integ (quadratic_spline * spline, double z0, double z)
{
	int i = check_and_search (spline, z);
	int j = check_and_search (spline, z0);

	double anti_derivative (int i, double z)
	{
		double h = z - spline->x[i]; 

        	return h*(spline->y[i] + h*(spline->b[i]/2 + h*spline->c[i]/3));
	}

	double integral = anti_derivative (i, z) - anti_derivative (i, spline->x[i]);

	while (i > j)
	{
		i--;
		integral += anti_derivative (i, spline->x[i + 1]) - anti_derivative (i, spline->x[i]);
	}	


	return integral; 
}

double quadratic_spline_deriv (quadratic_spline * spline, double z)
{
	int i = check_and_search (spline, z);
	double h = z - spline->x[i]; 

	return spline->b[i] + h*2.*spline->c[i];
}

void quadratic_spline_free (quadratic_spline * spline)
{
	free (spline->x);
	free (spline->y);

	free (spline->b);
	free (spline->c);

	free (spline);
}
