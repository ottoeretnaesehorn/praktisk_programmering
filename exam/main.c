#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_sort_vector.h>
#include "bilinear.h"

void set_random_vector (gsl_vector * vector)
{
	srand (time (0)); 

	for (int i = 0; i < vector->size; i++)
	{
		gsl_vector_set (vector, i, 10*(double)rand()/(double)RAND_MAX);
	}
}

void set_random_matrix (gsl_matrix * matrix)
{

	srand (time (0)); 

	for (int i = 0; i < matrix->size1; i++)
	{
		for (int j = 0; j < matrix->size2; j++)
		{
			gsl_matrix_set (matrix, i, j, 10*(double)rand()/(double)RAND_MAX);
		}	
	}
}

int main ()
{
	// Creating data for plot
	gsl_vector * x = gsl_vector_alloc (10);		// x dimensionality 
	set_random_vector (x);
       	gsl_sort_vector (x);	

	gsl_vector * y = gsl_vector_alloc (10);  	// y dimensionality
	set_random_vector (y);
	gsl_sort_vector (y); 

	gsl_matrix * F = gsl_matrix_alloc (x->size, y->size);
       	set_random_matrix (F); 

	// Writing the points to a txt-file
	FILE * data = fopen ("data.txt", "w"); 

	for (int i = 0; i < x->size; i++)
	{
		for (int j = 0; j < y->size; j++)
		{
			fprintf (data, "%g %g %g \n", 
					gsl_vector_get (x, i),
					gsl_vector_get (y, j), 
					gsl_matrix_get (F, i, j)
				);
		}

		fprintf (data, "\n"); 
	}

	fclose (data); 

	// The interpolation
	double inc = 0.1;	// Plot grid size

	double x_min = gsl_vector_get (x, 0), x_max = gsl_vector_get (x, x->size - 1);
	double y_min = gsl_vector_get (y, 0), y_max = gsl_vector_get (y, y->size - 1);

	FILE * out = fopen ("out.txt", "w"); 

	for (double dx = x_min; dx <= x_max; dx += inc)
	{
		for (double dy = y_min; dy <= y_max; dy += inc)
		{
			fprintf (out, "%g %g %g \n", dx, dy, bilinear (x, y, F, dx, dy)); 
		}
		
		fprintf (out, "\n"); 	
	}	

	fclose (out); 

	return 0; 
}
