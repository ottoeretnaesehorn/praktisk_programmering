#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include "jacobi.h"
#include "printing.h"

void create_symmetric_matrix (gsl_matrix * A, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			gsl_matrix_set (A, i, j, (double) 10*rand()/RAND_MAX);
			gsl_matrix_set (A, j, i, gsl_matrix_get (A, i, j));
		}
	}
}

int main ()
{
	int n = rand()%5 + 2;

	gsl_matrix * A = gsl_matrix_alloc (n, n); 
	create_symmetric_matrix (A, n);

	gsl_matrix * V = gsl_matrix_alloc (n, n);
	gsl_matrix_set_identity (V);

	gsl_matrix * Id = gsl_matrix_alloc (n, n);
	gsl_matrix_set_identity (Id);

	printf ("Randomly generated matrix: \n");
	print_matrix (stdout, "A = ", A);

	jacobi_diagonalisation (A, V);
	
	printf ("\nAfter diagonalisation: \n");
	print_matrix (stdout, "D = ", A);
	print_matrix (stdout, "V = ", V);

	gsl_matrix * VTAV = gsl_matrix_alloc (n, n);
	gsl_matrix * VDVT = gsl_matrix_alloc (n, n);
	gsl_matrix * VTV = gsl_matrix_alloc (n, n);
	
	printf ("\nTesting properties: \n");

	gsl_blas_dgemm (CblasTrans, CblasNoTrans, 1, V, V, 0, VTV);
	print_matrix (stdout, "V^T*V = ", VTV);

	gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, 1, V, A, 0, VDVT);
	gsl_blas_dgemm (CblasNoTrans, CblasTrans, 1, A, V, 0, VDVT);
	print_matrix (stdout, "V*D*V^T = ", VDVT);





	gsl_matrix_free (A);
	gsl_matrix_free (V);
	gsl_matrix_free (VTAV);
	gsl_matrix_free (VDVT);
	gsl_matrix_free (VTV);

	return 0;
}
