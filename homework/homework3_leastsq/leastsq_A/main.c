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

	least_squares (m, function, t, y, error, coefficients); 
	
	double fit (double x)
	{
		double s = 0; 

		for (int i = 0; i < m; i++)
		{
			s += gsl_vector_get (coefficients, i)*function(i, x);
		}

		return s; 
	}

	FILE * data = fopen ("data.txt", "w");
	for (int i = 0; i < n; i++)
	{
		fprintf (data, "%g %g %g \n", time[i], activity[i], 0.05*activity[i]); 
	}
	fclose (data); 

	FILE * plot = fopen ("plot.txt", "w");
	for (double x = time[0]; x <= time[n - 1]; x += (time[n - 1] - time[0])/64)
	{
		fprintf (plot, "%g %g \n", x, exp(fit (x)));
	}
	fclose (plot); 

	double half_life = -1/gsl_vector_get (coefficients, 1)*log(2.0);

	FILE * out = fopen ("out.txt", "w");
	fprintf (out, "Half-life = %.3g days \t \t (From fit)\n", half_life); 
	fprintf (out, "Half-life = 3.6319(23) days \t (Tabelvalue) \n"); 
	fclose (out);

	return 0; 
}
