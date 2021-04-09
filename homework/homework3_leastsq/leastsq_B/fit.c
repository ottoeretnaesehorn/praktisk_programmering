#include <stdio.h>
#include <math.h>
#include "least_squares.h"
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

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
	
	double c_1 = gsl_vector_get (coefficients, 1);
	double half_life = -1/c_1*log (2.0);
	double half_life_uncertainty = sqrt(gsl_matrix_get (S, 1, 1))/c_1/c_1;

	printf ("Half-life = %.3g +/- %.2g days \t (From fit) \n", half_life, half_life_uncertainty);
	printf ("Half-life = 3.6319(23) days \t (Tabelvalue) \n");
	
	return 0; 
}
