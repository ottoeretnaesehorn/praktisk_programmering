#include <assert.h>
#include <stdlib.h>
#include "value_check.h"
#include "binary_search.h"

typedef struct 
{
	int n; 
	
	double * x; 
	double * y; 
	
	double * coefficient_b; 
	double * coefficient_c; 
} 
quadratic_spline;

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

	double dx[n - 1];
	double dydx[n - 1];

	for (int i = 0; i < n - 1; i++)
	{
		dx[i] = x[i + 1] - x[i];
		assert (dx[i] > 0);
	
		dydx[i] = (y[i + 1] - y[i])/dx[i]; 
	}

	spline->coefficient_c = (double *) malloc ((n - 1)*sizeof (double)); 

	spline->coefficient_c[0] = 0; 

	for (int i = 0; i < n - 2; i++)
	{
		spline->coefficient_c[i + 1] = (dydx[i + 1] - dydx[i] - (spline->coefficient_c[i])*dx[i])/dx[i + 1];
	}

	spline->coefficient_c[n - 2] /= 2; 

	for (int i = n - 3; i >= 0; i--)
	{
		spline->coefficient_c[i] = (dydx[i + 1] - dydx[i] - (spline->coefficient_c[i + 1])*dx[i + 1])/dx[i]; 
	}	

	spline->coefficient_b = (double *) malloc ((n - 1)*sizeof (double));

	for (int i = 0; i < n - 1; i++)
	{
		spline->coefficient_b[i] = dydx[i] - (spline->coefficient_c[i])*dx[i]; 
	}	

	return spline; 
}

double quadratic_spline_eval (quadratic_spline * spline, double z)
{
	value_check (spline->n, spline->x, z); 

	int i = binary_search (spline->n, spline-> x, spline->y, z);
	
	return spline->y[i] 
		+ (z - spline->x[i])*(spline->coefficient_b[i] 
				+ (z - spline->x[i])*spline->coefficient_c[i]);
}

double quadratic_spline_integ (quadratic_spline * spline, double z)
{
	value_check (spline->n, spline->x, z);

	int i = binary_search (spline->n, spline->x, spline->y, z);

	double anti_derivative (quadratic_spline * spline, int i, double z)
	{
        	return (z - spline->x[i])*(spline->y[i] 
				+ (z - spline->x[i])*(spline->coefficient_b[i]/2 
					+ (z - spline->x[i])*spline->coefficient_c[i]/3));
	}

	double integral = anti_derivative (spline, i, z); 

	while (i > 0)
	{
		i--;
		integral += anti_derivative (spline, i, spline->x[i + 1]);
	}

	return integral; 
}

double quadratic_spline_deriv (quadratic_spline * spline, double z)
{
	value_check (spline->n, spline->x, z);

	int i = binary_search (spline->n, spline->x, spline->y, z);

	return spline->coefficient_b[i] + 
		(z - spline->x[i])*2.*spline->coefficient_c[i];
}

void quadratic_spline_free (quadratic_spline * spline)
{
	free (spline->x);
	free (spline->y);

	free (spline->coefficient_b);
	free (spline->coefficient_c);

	free (spline);
}
