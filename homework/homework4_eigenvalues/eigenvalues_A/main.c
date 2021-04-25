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

	gsl_matrix * D = gsl_matrix_alloc (n, n); 
	gsl_matrix_memcpy (D, A);

	gsl_matrix * V = gsl_matrix_alloc (n, n);
	gsl_matrix_set_identity (V);

	printf ("Randomly generated matrix: \n\n");
	print_matrix ("A = ", A);

	jacobi_diagonalisation (D, V);
	
	printf ("\nAfter diagonalisation: \n\n");
	print_matrix ("D = ", D);
	printf ("\n");
	print_matrix ("V = ", V);

	printf ("\nTesting properties: \n\n");

	gsl_matrix * VTV = gsl_matrix_alloc (n, n);
	gsl_blas_dgemm (CblasTrans, CblasNoTrans, 1, V, V, 0, VTV);
	print_matrix ("VTV = ", VTV);
	printf ("\n");

	gsl_matrix * VTA = gsl_matrix_alloc (n, n); 
	gsl_matrix * VTAV = gsl_matrix_alloc (n, n);
	gsl_blas_dgemm (CblasTrans, CblasNoTrans, 1, V, A, 0, VTA); 
	gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, 1, VTA, V, 0, VTAV); 
       	print_matrix ("VTAV = ", VTAV);	
	printf ("\n");

	gsl_matrix * VD = gsl_matrix_alloc (n, n);
	gsl_matrix * VDVT = gsl_matrix_alloc (n, n); 
	gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, 1, V, D, 0, VD); 
	gsl_blas_dgemm (CblasNoTrans, CblasTrans, 1, VD, V, 0, VDVT);
      	print_matrix ("VDVT = ", VDVT); 	

	gsl_matrix_free (A);
	gsl_matrix_free (D);
	gsl_matrix_free (V);

	gsl_matrix_free (VTV);
	gsl_matrix_free (VTA);
	gsl_matrix_free (VTAV);
	gsl_matrix_free (VD);
	gsl_matrix_free (VDVT);

	return 0;
}
