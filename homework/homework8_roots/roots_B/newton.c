#include <float.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "newton.h"

int newton (void f (gsl_vector * x, gsl_vector * fx), gsl_vector * x, double eps)
{
	int n = x->size; 
	int steps = 0; 

	double delta = sqrt(DBL_EPSILON); 
	int limit = 1000; 

	gsl_vector * fx = gsl_vector_alloc (n); 
	gsl_vector * x_new = gsl_vector_alloc (n); 
	gsl_vector * fx_new = gsl_vector_alloc (n); 

	gsl_matrix * J = gsl_matrix_alloc (n, n); 
	gsl_vector * tau = gsl_vector_alloc (n); 
	gsl_vector * df = gsl_vector_alloc (n); 
	gsl_vector * dx = gsl_vector_alloc (n); 

	while (steps < limit)
	{
		f (x, fx); 

		for (int i = 0; i < n; i++)
		{
			double x_i = gsl_vector_get (x, i); 
			gsl_vector_set (x, i, x_i + delta); 

			f (x, df); 
			gsl_vector_sub (df, fx); 
			
			for (int j = 0; j < n; j++)
			{
				gsl_matrix_set (J, j, i, gsl_vector_get (df, j)/delta); 
			}		

			gsl_vector_set (x, i, x_i);
		}

		gsl_linalg_QR_decomp (J, tau); 
		gsl_linalg_QR_solve (J, tau, fx, dx); 
		gsl_vector_scale (dx, -1.0);

		double s = 1.0; 

		while (s > 1./64)
		{
			gsl_vector_memcpy (x_new, x); 
			gsl_vector_add (x_new, dx); 
			
			f(x_new, fx_new); 

			if (gsl_blas_dnrm2 (fx_new) < (1 - s/2)*gsl_blas_dnrm2 (fx))
			{
				break; 
			}

			s *= 0.5; 
			gsl_vector_scale (dx, 0.5); 
		}	

		gsl_vector_memcpy (x, x_new); 
		gsl_vector_memcpy (fx, fx_new); 

		if (gsl_blas_dnrm2 (dx) < delta || gsl_blas_dnrm2 (fx) < eps)
		{
			break;
		}

		steps++; 
	}

	gsl_vector_free (fx); 
	gsl_vector_free (x_new); 
	gsl_vector_free (fx_new); 

	gsl_matrix_free (J); 
	gsl_vector_free (tau); 
	gsl_vector_free (df); 
	gsl_vector_free (dx); 

	return steps;
}
