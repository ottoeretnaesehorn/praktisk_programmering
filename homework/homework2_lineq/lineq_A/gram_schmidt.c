#include <math.h>
#include <assert.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include "gram_schmidt.h"

void GS_decomposition (gsl_matrix * A, gsl_matrix * R)
{
	assert (A->size2 == R->size1 && R->size1 == R->size2); 

	int n = A->size1;
	int m = A->size2;

	gsl_vector * ai = gsl_vector_alloc (n); 
	gsl_vector * aj = gsl_vector_alloc (n);

	double aiaj;
	
	for (int i = 0; i < m; i++)
	{
		gsl_matrix_get_col (ai, A, i);

		gsl_matrix_set (R, i, i, gsl_blas_dnrm2 (ai));
		gsl_vector_scale (ai, 1./gsl_matrix_get(R, i, i));
		gsl_matrix_set_col (A, i, ai);

		for (int j = i + 1; j < m; j++)
		{
			gsl_matrix_get_col (aj, A, j);
			
			gsl_blas_ddot (ai, aj, &aiaj);
			
			gsl_vector_scale (aj, 1./aiaj);
			gsl_vector_sub (aj, ai);
			gsl_vector_scale (aj, aiaj);

			gsl_matrix_set_col (A, j, aj);
			gsl_matrix_set (R, i, j, aiaj);
		    	gsl_matrix_set (R, j, i, 0);	
		}	
	}

	gsl_vector_free (ai);
	gsl_vector_free (aj);
}

void back_substitution (gsl_matrix * U, gsl_vector * c)
{
        for (int i = c->size - 1; i >= 0; i--)
        {
                double sum = gsl_vector_get (c, i);

                for (int j = i + 1; j < c->size; j++)
                {
                        sum -= gsl_matrix_get (U, i, j)*gsl_vector_get (c, j);
                }

                gsl_vector_set (c, i, sum/gsl_matrix_get (U, i, i));
        }
}

void GS_solve (gsl_matrix * Q, gsl_matrix * R, gsl_vector * b, gsl_vector * x)
{
	gsl_blas_dgemv (CblasTrans, 1.0, Q, b, 0.0, x);
     	back_substitution (R, x);	
}
