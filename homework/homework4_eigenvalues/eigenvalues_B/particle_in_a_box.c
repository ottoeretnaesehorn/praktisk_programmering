#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include "jacobi.h"
#include "printing.h"

gsl_matrix * hamiltonian (int n)
{
	gsl_matrix * H = gsl_matrix_alloc (n, n); 

	for (int i = 0; i < n - 1; i++)
	{
		gsl_matrix_set (H, i, i, -2); 
		gsl_matrix_set (H, i, i + 1, 1); 
		gsl_matrix_set (H, i + 1, i, 1); 
	}

	gsl_matrix_set (H, n - 1, n - 1, -2); 

	double s = 1.0/(n + 1); 
	gsl_matrix_scale (H, -1.0/s/s);

	return H; 	
}

int main ()
{
	int n = 20; 

	gsl_matrix * H = gsl_matrix_alloc (n, n); 
	H = hamiltonian (n); 

	gsl_matrix * eigenvectors = gsl_matrix_alloc (n, n);
       	gsl_matrix_set_identity (eigenvectors);	
	
	gsl_matrix * eigenvalues = gsl_matrix_alloc (n, n); 
	gsl_matrix_memcpy (eigenvalues, H); 

	jacobi_diagonalisation (eigenvalues, eigenvectors); 

	printf ("Eigenvalue \t Exact \t \t Calculated \t Difference \n");
	
	for (int i = 0; i < n; i++)
	{
		double exact = M_PI*M_PI*(i + 1)*(i + 1); 
	       	double calculated = gsl_matrix_get (eigenvalues, i, i);

		printf ("%i \t \t %10g \t %10g \t %10g \n", i, exact, calculated, fabs(exact - calculated)); 	
	}

	printf ("\n \n");
	printf ("Eigenvectors: \n");
	printf ("Exact \t Calculated \n");

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; i < n; i ++)
		{
			printf ("%g \t %g \n", (i + 1.0)/(n + 1), gsl_matrix_get (eigenvectors, j, i));
		}
	}

	return 0;
}
