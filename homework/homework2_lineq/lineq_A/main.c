#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include "gram_schmidt.h"
#include "printing.h"

void create_matrix_and_vector (int n, int m, gsl_matrix * A, gsl_vector * b)
{
	for (int i = 0; i < n; i++)
	{
		gsl_vector_set (b, i, (double) 10*rand()/RAND_MAX);

		for (int j = 0; j < m; j++)
		{
			gsl_matrix_set (A, i, j, (double) 10*rand()/RAND_MAX);
		}
	}
}

int main ()
{
	int n = rand()%5 + 1; 
	int m = n; 

	gsl_matrix * A = gsl_matrix_alloc (n, m);
	gsl_matrix * Q = gsl_matrix_alloc (n, m);
	gsl_matrix * R = gsl_matrix_alloc (m, m);
	gsl_matrix * QTQ = gsl_matrix_alloc (m, m);
	gsl_matrix * QR = gsl_matrix_alloc (n, m);

	gsl_vector * b = gsl_vector_alloc (n);
	gsl_vector * x = gsl_vector_alloc (m); 
	gsl_vector * Ax = gsl_vector_alloc (n);

	create_matrix_and_vector (n, m, A, b);
	gsl_matrix_memcpy (Q, A);

	printf ("Linear equation Ax=b, with: \n");
	print_matrix ("A = ", A);
	print_vector ("b = ", b);

	GS_decomposition (Q, R);

	printf ("\nAfter Gram-Schmidt QR-decomposition: \n");
	print_matrix ("Q = ", Q);
	print_matrix ("R = ", R);
	
	printf ("\nTesting properties of decomposition: \n");

	gsl_blas_dgemm (CblasTrans, CblasNoTrans, 1.0, Q, Q, 0.0, QTQ);
	print_matrix ("QTQ = ", QTQ);

	gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, 1.0, Q, R, 0.0, QR);
	print_matrix ("QR = ", QR);

	GS_solve (Q, R, b, x); 
	gsl_blas_dgemv (CblasNoTrans, 1, A, x, 0, Ax);

	printf ("\nTesting properties of solve: \n");
	print_vector ("x = ", x);
	print_vector ("Ax = ", Ax);

	gsl_matrix_free (A);
	gsl_matrix_free (Q);
	gsl_matrix_free (R);
	gsl_matrix_free (QTQ);
	gsl_matrix_free (QR);

	gsl_vector_free (b);
	gsl_vector_free (x);
	gsl_vector_free (Ax);

	return 0;
}
