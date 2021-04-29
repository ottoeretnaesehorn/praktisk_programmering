#include <stdio.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include "least_squares.h"

int main ()
{
	double time[] = {1, 2, 3, 4, 6, 9, 10, 13, 15}; 
	double activity[] = {117, 100, 88, 72, 53, 29.5, 25.2, 15.2, 11.1}; 

	int n = sizeof (time)/sizeof (time[0]);

	gsl_vector * t = gsl_vector_alloc (n); 
	gsl_vector * y = gsl_vector_alloc (n); 
	gsl_vector * error = gsl_vector_alloc (n); 

	for (int i = 0; i < n; i++)
	{
		gsl_vector_set (t, i, time[i]);
		gsl_vector_set (y, i, log(activity[i]));
		gsl_vector_set (error, i, 0.05);
	}

	double function (int i, double t)
	{
		switch (i)
		{
			case 0 : 
				return 1; 
				break;
			case 1 : 
				return t; 
				break;
			default : 
				return NAN; 
		}
	}

	int m = 2;
	gsl_vector * coefficients = gsl_vector_alloc (m); 
	gsl_matrix * S = gsl_matrix_alloc (m, m); 

	least_squares (m, function, t, y, error, coefficients, S); 
	
	double fit (double x)
	{
		double fit_value = 0; 

		for (int i = 0; i < m; i++)
		{
			fit_value += gsl_vector_get (coefficients, i)*function(i, x);
		}

		return fit_value; 
	}

	double fit_plus_uncertainty (double x)
	{
		double fit_value = 0;

		for (int i = 0; i < m; i++)
		{
			fit_value += (gsl_vector_get (coefficients, i) + sqrt(gsl_matrix_get (S, i, i)))*function(i, x);  
		}

		return fit_value;
	}

	double fit_minus_uncertainty (double x)
	{
		double fit_value = 0;

		for (int i = 0; i < m; i++)
		{
			fit_value += (gsl_vector_get (coefficients, i) - sqrt(gsl_matrix_get (S, i, i)))*function(i, x);  
		}

		return fit_value;
	}

	FILE * points = fopen ("points.txt", "w");
	for (int i = 0; i < n; i++)
	{
		fprintf (points, "%g %g %g \n", time[i], activity[i], 0.05*activity[i]); 
	}
	fclose (points); 

	FILE * data = fopen ("data.txt", "w");
	for (double x = time[0]; x <= time[n - 1]; x += (time[n - 1] - time[0])/64)
	{
		fprintf (data, "%g %g %g %g \n", x, exp(fit (x)), 
				exp(fit_plus_uncertainty (x)), exp(fit_minus_uncertainty (x)));
	}
	fclose (data); 

	double c_1 = gsl_vector_get (coefficients, 1);
	double half_life = -log(2.0)/c_1;
	double half_life_uncertainty = sqrt(gsl_matrix_get (S, 1, 1))/c_1/c_1;

	FILE * out = fopen ("out.txt", "w");
	fprintf (out, "Half-life = %.3g +/- %.2g days \t (From fit)\n", half_life, half_life_uncertainty); 
	fprintf (out, "Half-life = 3.6319(23) days \t (Tabelvalue) \n"); 
	
	fclose (out);

	return 0; 
}
