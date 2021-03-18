#include <assert.h>
#include <stdlib.h>
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



quadratic_spline * quadratic_spline_alloc (int n, double * x, double * y)
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

double quadratic_spline_evaluator (quadratic_spline * spline, double z)
{
	assert (z >= (spline -> x[0]) && z <= (spline -> x[(spline -> n) - 1]));

	int i = binary_search (spline -> n, spline -> x, spline -> y, z);
	
	return (spline -> y[i]) + (z - (spline -> x[i]))*((spline -> coefficient_b[i]) + (z - (spline -> x[i]))*(spline -> coefficient_c[i]));
}

void quadratic_spline_free (quadratic_spline * spline)
{
	free (spline -> x);
	free (spline -> y);

	free (spline -> coefficient_b);
	free (spline -> coefficient_c);

	free (spline);
}



double linear_spline (int n, double x[], double y[], double z)
{
	assert (n > 1 && z >= x[0] && z <= x[n - 1]); 

	int i = binary_search (n, x, y, z); 	

	double dx = x[i + 1] - x[i]; 
	double dy = y[i + 1] - y[i]; 

	assert (dx > 0); 

	return y[i] + dy/dx*(z - x[i]); 
}

double linear_anti_derivative (int i, double x[], double y[], double z)
{
	double dx = x[i + 1] - x[i]; 
	double dy = y[i + 1] - y[i]; 

	assert (dx > 0); 
	
	return (z - x[i])*(y[i] + dy/dx*(z - x[i])/2); 
}

double linear_spline_integrator (int n, double x[], double y[], double z_0,  double z)
{
	assert (n > 1 && z >= x[0] && z <= x[n - 1]); 

	int i = binary_search (n, x, y, z); 	
	int j = binary_search (n, x, y, z_0);

	double integral = linear_anti_derivative (i, x, y, z) - linear_anti_derivative (i, x, y, x[i]);
	i--;

	while (i >= j)
	{
		integral += linear_anti_derivative (i, x, y, x[i + 1]) - linear_anti_derivative (i, x, y, x[i]);
		i--;
	}


	return integral;
}
