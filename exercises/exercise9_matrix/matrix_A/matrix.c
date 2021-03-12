#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "matrix_copy.h"

int main() 
{
	gsl_matrix * A = gsl_matrix_alloc (3, 3);
	gsl_vector * b = gsl_vector_alloc (3);
	gsl_vector * x = gsl_vector_calloc (3);

	gsl_matrix_set (A, 0, 0, 6.13);
	gsl_matrix_set (A, 0, 1, -2.90);
	gsl_matrix_set (A, 0, 2, 5.86);
	gsl_matrix_set (A, 1, 0, 8.08);
	gsl_matrix_set (A, 1, 1, -6.31);
	gsl_matrix_set (A, 1, 2, -3.89);
	gsl_matrix_set (A, 2, 0, -4.36);
	gsl_matrix_set (A, 2, 1, 1.00);
	gsl_matrix_set (A, 2, 2, 0.19);

	gsl_matrix * A_copy = gsl_matrix_alloc(3, 3);
       	A_copy = matrix_copy(A);

	gsl_vector_set (b, 0, 6.23);
	gsl_vector_set (b, 1, 5.37);
	gsl_vector_set (b, 2, 2.29);

	gsl_linalg_HH_solve(A, b, x);

	gsl_vector * Ax = gsl_vector_calloc (3);
	gsl_blas_dgemv(CblasNoTrans, 1, A_copy, x, 0, Ax);

	printf("b = (%f, %f, %f)\n", gsl_vector_get (b, 0), gsl_vector_get (b, 1), gsl_vector_get (b, 2));
	printf("A*x = (%f, %f, %f)\n", gsl_vector_get (Ax, 0), gsl_vector_get (Ax, 1), gsl_vector_get (Ax, 2));

	gsl_matrix_free (A);
	gsl_vector_free (b);
	gsl_vector_free (x);
	gsl_vector_free (Ax);

	return 0; 
}
