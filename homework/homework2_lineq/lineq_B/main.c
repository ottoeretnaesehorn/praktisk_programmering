#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include "gram_schmidt.h"
#include "printing.h"

void create_matrix (int n, gsl_matrix * A)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			gsl_matrix_set (A, i, j, (double) 10*rand()/RAND_MAX);
		}
	}
}

int main ()
{
	int n = rand()%5 + 1; 

	gsl_matrix * A = gsl_matrix_alloc (n, n);
	gsl_matrix * Q = gsl_matrix_alloc (n, n);
	gsl_matrix * R = gsl_matrix_alloc (n, n);
	gsl_matrix * B = gsl_matrix_alloc (n, n);
	gsl_matrix * AB = gsl_matrix_alloc (n, n);
	gsl_matrix * BA = gsl_matrix_alloc (n, n);

	create_matrix (n, A);
	gsl_matrix_memcpy (Q, A);

	printf ("Randomly generated matrix: \n");
	print_matrix ("A = ", A);

	GS_decomposition (Q, R);
	GS_inverse (Q, R, B);

	gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, 1.0, A, B, 0.0, AB);	
	gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, 1.0, B, A, 0.0, BA);	
	
	print_matrix("\nAB = ", AB);
	print_matrix("BA = ", BA); 

	gsl_matrix_free (A);
	gsl_matrix_free (Q);
	gsl_matrix_free (R);
	gsl_matrix_free (B);
	gsl_matrix_free (AB);
	gsl_matrix_free (BA);

	return 0;
}
