#include <stdio.h>
#include <stdlib.h>
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
	int m = rand()%5 + 1; 

	if (n < m || n == m)
	{
		n = m + 1; 
	}

	gsl_matrix * A = gsl_matrix_alloc (n, m);
	gsl_matrix * Q = gsl_matrix_alloc (n, m);
	gsl_matrix * R = gsl_matrix_alloc (m, m);
	gsl_matrix * QTQ = gsl_matrix_alloc (m, m);
	gsl_matrix * QR = gsl_matrix_alloc (n, m);

	gsl_vector * b = gsl_vector_alloc (n);
	gsl_vector * x = gsl_vector_alloc (m); 
	gsl_vector * Ax = gsl_vector_alloc (n);

	gsl_matrix * Id = gsl_matrix_alloc (m, m);
	gsl_matrix_set_identity (Id); 

	create_matrix_and_vector (n, m, A, b);
	gsl_matrix_memcpy (Q, A);

	FILE * out = fopen ("./out.txt", "w");

	fprintf (out, "Linear equation Ax=b, with: \n");
	print_matrix (out, "A = ", A);
	print_vector (out, "b = ", b);

	GS_decomposition (Q, R);

	fprintf (out, "\nAfter Gram-Schmidt QR-decomposition: \n");
	print_matrix (out, "Q = ", Q);
	print_matrix (out, "R = ", R);
	
	fprintf (out, "\nTesting properties of decomposition: \n");

	gsl_blas_dgemm (CblasTrans, CblasNoTrans, 1, Q, Q, 0, QTQ);
	print_matrix (out, "QTQ = ", QTQ);

	gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, 1, Q, R, 0, QR);
	print_matrix (out, "QR = ", QR);

	GS_solve (Q, R, b, x); 
	gsl_blas_dgemv (CblasNoTrans, 1, A, x, 0, Ax);

	fprintf (out, "\nTesting properties of solve: \n");
	print_vector (out, "x = ", x);
	print_vector (out, "Ax = ", Ax);

	fclose (out);

	gsl_matrix_free (A);
	gsl_matrix_free (Q);
	gsl_matrix_free (R);
	gsl_matrix_free (QTQ);
	gsl_matrix_free (QR);

	gsl_vector_free (b);
	gsl_vector_free (x);
	gsl_vector_free (Ax);

	gsl_matrix_free (Id);

	return 0;
}
