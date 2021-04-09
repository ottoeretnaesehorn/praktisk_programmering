#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include "gram_schmidt.h"

void least_squares (
		int m, double f (int i, double x),
		gsl_vector * x, gsl_vector * y, gsl_vector * error,
		gsl_vector * c)
{
	int n = x->size; 

	gsl_matrix * A = gsl_matrix_alloc (n, m); 
	gsl_matrix * R = gsl_matrix_alloc (m, m); 
	gsl_vector * b = gsl_vector_alloc (n); 

	for (int i = 0; i < n; i++)
	{
		double x_i = gsl_vector_get (x, i); 
		double y_i = gsl_vector_get (y, i); 
		double error_i = gsl_vector_get (error, i); 

		gsl_vector_set (b, i, y_i/error_i); 

		for (int j = 0; j < m; j++)
		{
			gsl_matrix_set (A, i, j, f(j, x_i)/error_i); 
		}
	}

	GS_decomposition (A, R); 
	GS_solve (A, R, b, c); 

	gsl_matrix_free (A); 
	gsl_matrix_free (R); 
	gsl_vector_free (b); 
}
