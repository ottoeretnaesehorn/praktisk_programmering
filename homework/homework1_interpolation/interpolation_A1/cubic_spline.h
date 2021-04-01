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
	double * coefficient_d;	
} 
cubic_spline;

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

	double dx[n - 1];
	double dydx[n - 1];

	for (int i = 0; i < n - 1; i++)
	{
		dx[i] = x[i + 1] - x[i];
		assert (dx[i] > 0);
	
		dydx[i] = (y[i + 1] - y[i])/dx[i]; 
	}

	double tridiagonal_main[n];
	double tridiagonal_above_main[n - 1];
	double tridiagonal_right_hand[n];

	tridiagonal_main[0] = 2; 
	tridiagonal_main[n - 1] = 2; 

	for (int i = 0; i < n - 2; i++)
	{
		tridiagonal_main[i + 1] = 2.*dx[i]/dx[i + 1] + 2.;
	}

	tridiagonal_above_main[0] = 1; 

	for (int i = 0; i < n - 2; i++)
	{
		tridiagonal_above_main[i + 1] = dx[i]/dx[i + 1]; 
	}

	tridiagonal_right_hand[0] = 3*dydx[0]; 
	tridiagonal_right_hand[n - 1] = 3*dydx[n - 2];

	for (int i = 1; i < n; i++)
	{
		tridiagonal_main[i] -= tridiagonal_above_main[i - 1]/tridiagonal_main[i - 1];
		tridiagonal_right_hand[i] -= tridiagonal_right_hand[i - 1]/tridiagonal_main[i - 1];
	}
	
	spline->coefficient_b = (double *) malloc (n*sizeof (double));
	spline->coefficient_c = (double *) malloc ((n - 1)*sizeof (double));
	spline->coefficient_d = (double *) malloc ((n - 1)*sizeof (double));

	spline->coefficient_b[n - 1] = tridiagonal_right_hand[n - 1]/tridiagonal_main[n - 1];

	for (int i = n - 2; i >= 0; i--)
	{
		spline->coefficient_b[i] = (tridiagonal_right_hand[i] 
				- tridiagonal_above_main[i]*spline->coefficient_b[i + 1])/tridiagonal_main[i];
	}

	for (int i = 0; i < n - 1; i++)
	{
		spline->coefficient_c[i] = (-2*spline->coefficient_b[i]
				- spline->coefficient_b[i + 1]
				+ 3*dydx[i])/dx[i];
		spline->coefficient_d[i] = (spline->coefficient_b[i] 
				+ spline->coefficient_b[i + 1] 
				- 2*dydx[i])/dx[i]/dx[i];
	}

	return spline; 
}

double cubic_spline_eval (cubic_spline * spline, double z)
{
	value_check (spline->n, spline->x, z); 

	int i = binary_search (spline->n, spline-> x, spline->y, z);
	
	return spline->y[i] 
		+ (z - spline->x[i])*(spline->coefficient_b[i] 
				+ (z - spline->x[i])*(spline->coefficient_c[i]
				+ (z - spline->x[i])*spline->coefficient_d[i]));
}

double cubic_spline_integ (cubic_spline * spline, double z)
{
	value_check (spline->n, spline->x, z);

	int i = binary_search (spline->n, spline->x, spline->y, z);

	double anti_derivative (cubic_spline * spline, int i, double z)
	{
        	return (z - spline->x[i])*(spline->y[i] 
				+ (z - spline->x[i])*(spline->coefficient_b[i]/2 
					+ (z - spline->x[i])*(spline->coefficient_c[i]/3
						+ (z - spline->x[i])*spline->coefficient_d[i]/4)));
	}

	double integral = anti_derivative (spline, i, z); 

	while (i > 0)
	{
		i--;
		integral += anti_derivative (spline, i, spline->x[i + 1]);
	}

	return integral; 
}


double cubic_spline_deriv (cubic_spline * spline, double z)
{
	value_check (spline->n, spline->x, z);

	int i = binary_search (spline->n, spline->x, spline->y, z);

	return spline->coefficient_b[i] + 
		(z - spline->x[i])*(2.*spline->coefficient_c[i]
		+ (z - spline->x[i])*3.*spline->coefficient_d[i]);
}

void cubic_spline_free (cubic_spline * spline)
{
	free (spline->x);
	free (spline->y);

	free (spline->coefficient_b);
	free (spline->coefficient_c);
	free (spline->coefficient_d);

	free (spline);
}
