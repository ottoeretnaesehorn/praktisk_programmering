#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include "gram_schmidt.h"

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

	clock_t start, end; 
	clock_t start_gsl, end_gsl;

	double runtime; 
	double runtime_gsl; 

	for (int n = 1; n < 100; n++)
	{
		gsl_matrix * A = gsl_matrix_alloc (n, n);
		gsl_matrix * Q = gsl_matrix_alloc (n, n);
		gsl_matrix * R = gsl_matrix_alloc (n, n);
		gsl_vector * tau = gsl_vector_alloc (n); 
		
		create_matrix (n, A);
		gsl_matrix_memcpy (A, Q);

		start = clock (); 
		GS_decomposition (A, R); 
		end = clock ();
		runtime = (double) (end - start)/CLOCKS_PER_SEC;

		start_gsl = clock ();
		gsl_linalg_QR_decomp (Q, tau);
		end_gsl = clock (); 	
		runtime_gsl = (double) (end_gsl - start_gsl)/CLOCKS_PER_SEC;

		printf ("%d \t %f \t %f \n", n, runtime, runtime_gsl);
	
		gsl_matrix_free (A);
		gsl_matrix_free (R);
		gsl_vector_free (tau);
	}

	return 0;
}
