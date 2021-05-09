#include <stdio.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include "quasi_newton.h"
#include "printing.h"

gsl_matrix * data_structure ()
{
	gsl_matrix * data = gsl_matrix_alloc (3, 30); 

	double cross_section[30] = {-0.25, -0.30, -0.15, -1.71, 0.81, 
		0.65, -0.91, 0.91, 0.96, -2.52,
		-1.01, 2.01, 4.83, 4.58, 1.26, 
		1.01, -1.26, 0.45, 0.15, -0.91, 
		-0.81, -1.41, 1.36, 0.50, -0.45,
		1.61, -2.21, -1.86, 1.76, -0.5};

	for (int i = 0; i < 30; i++)
	{
		gsl_matrix_set (data, 0, i, 101. + 2*i);
		gsl_matrix_set (data, 1, i, cross_section[i]);
		
		if (i < 2)
		{
			gsl_matrix_set (data, 2, i, 2.);
		}	
		else if (i < 8)
		{
			gsl_matrix_set (data, 2, i, 1.9); 
		}
		else if (i < 14)
		{
			gsl_matrix_set (data, 2, i, 1.6); 
		}
		else if (i < 20)
		{
			gsl_matrix_set (data, 2, i, 1.3); 
		}
		else if (i < 27)
		{
			gsl_matrix_set (data, 2, i, 1.1);
		}
		else 
		{
			gsl_matrix_set (data, 2, i, 0.9); 
		}
	}

	return data; 
}

double breit_wigner (double E, gsl_vector * parameters)
{
	double m = gsl_vector_get (parameters, 0); 
	double width = gsl_vector_get (parameters, 1); 
	double scale = gsl_vector_get (parameters, 2); 

	return scale/((E - m)*(E - m) + width*width/4.);
}

int main()
{
	gsl_matrix * data = data_structure ();

	double deviation (gsl_vector * parameters)
	{
		double result = 0; 

		for (int i = 0; i < data->size2; i++)
		{
			double E = gsl_matrix_get (data, 0, i); 
			double cross_section = gsl_matrix_get (data, 1, i);
			double error = gsl_matrix_get (data, 2, i);
			double F = breit_wigner (E, parameters); 

			result += (F - cross_section)*(F - cross_section)/error/error;
		}

		return result; 
	}

	gsl_vector * parameters = gsl_vector_alloc (3);
	gsl_vector_set (parameters, 0, 125.);
       	gsl_vector_set (parameters, 1, 6.5); 
	gsl_vector_set (parameters, 2, 15.0); 	

	quasi_newton (deviation, parameters, 1e-5);

	FILE * points = fopen ("points.txt", "w"); 

	for (int i = 0; i < data->size2; i++)
	{
		fprintf (points, "%g %g %g \n", 
				gsl_matrix_get (data, 0, i),
				gsl_matrix_get (data, 1, i), 
				gsl_matrix_get (data, 2, i));
	}	

	fclose (points);

	FILE * plot = fopen ("data.txt", "w"); 

	for (double E = 100.; E <= 160.; E += 0.5)
	{
		fprintf (plot, "%g %g\n", E, breit_wigner (E, parameters));  
	}	

	fclose (plot);

	printf ("The determined mass of the Higgs is %g GeV \n", gsl_vector_get (parameters, 0));	

	return 0; 
}
