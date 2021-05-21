#include <stdio.h>
#include <math.h>
#include <float.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include "quasi_newton.h"

double delta = sqrt (DBL_EPSILON); 

void numeric_gradient (
		double f (gsl_vector * x), 
		gsl_vector * x, 
		gsl_vector * gradient
		)
{
	double fx = f(x); 

	for (int i = 0; i < x->size; i++)
	{
		double dx; 
		double x_i = gsl_vector_get (x, i); 

		if (fabs (x_i) < sqrt (delta))
		{
			dx = delta; 
		}
		else
		{
			dx = fabs (x_i)*delta;
		}

		gsl_vector_set (x, i, x_i + dx); 
		gsl_vector_set (gradient, i, (f(x) - fx)/dx);
		gsl_vector_set (x, i, x_i); 
	}
}

int quasi_newton(
		double f (gsl_vector * x), 
	       	gsl_vector * x, 
		double acc	
		)
{
	int n = x->size; 
	int steps = 0, good_steps = 0, bad_steps = 0;

	gsl_matrix * B = gsl_matrix_alloc (n, n); 
	gsl_vector * gradient = gsl_vector_alloc (n); 

	gsl_vector * dx = gsl_vector_alloc (n); 
	gsl_vector * x_new = gsl_vector_alloc (n); 
	gsl_vector * gradient_new = gsl_vector_alloc (n);

	gsl_vector * dgradient = gsl_vector_alloc (n); 	
	gsl_vector * u = gsl_vector_alloc (n); 

	gsl_matrix_set_identity (B); 
	numeric_gradient (f, x, gradient);

	double fx = f(x);
	double fx_new; 

	while (steps < 1000)
	{
		steps++;

		gsl_blas_dgemv (CblasNoTrans, -1, B, gradient, 0, dx); 

		if (gsl_blas_dnrm2 (dx) < delta*gsl_blas_dnrm2 (x))
		{
			fprintf (stderr, "quasi_newton : |dx| < delta*|x| \n");
			break;
		}
		
		if (gsl_blas_dnrm2 (gradient) < acc)
		{
			fprintf (stderr, "quasi_newton : |gradient| < accuracy \n");
		        break;	
		}

		double lambda = 1; 
		
		while (1)
		{
			gsl_vector_memcpy (x_new, x); 
			gsl_vector_add (x_new, dx); 
			fx_new = f(x_new); 

			double sTgradient; 
			gsl_blas_ddot (dx, gradient, &sTgradient); 

			if (fx_new < fx + 0.01*sTgradient) 
			{
				good_steps++;
				break;
			}

			if (lambda < delta)
			{
				bad_steps++; 
				gsl_matrix_set_identity (B); 
				break;
			}

			lambda *= 0.5; 
			gsl_vector_scale (dx, 0.5); 
		}

		numeric_gradient (f, x_new, gradient_new);
	       	gsl_vector_memcpy (dgradient, gradient_new); 
		gsl_blas_daxpy (-1, gradient, dgradient); 

		gsl_vector_memcpy (u, dx); 
		gsl_blas_dgemv (CblasNoTrans, -1, B, dgradient, 1, u); 

		double sTdgradient, uTdgradient;
		gsl_blas_ddot (dx, dgradient, &sTdgradient); 

		if (fabs (sTdgradient) > 1e-12)
		{
			gsl_blas_ddot (u, dgradient, &uTdgradient);
			double gamma = uTdgradient/2/sTdgradient; 

			gsl_blas_daxpy (-gamma, dx, u); 
			gsl_blas_dger (1./sTdgradient, u, dx, B); 
			gsl_blas_dger (1./sTdgradient, dx, u, B); 
		}

		gsl_vector_memcpy (x, x_new); 
		gsl_vector_memcpy (gradient, gradient_new); 
	}

	gsl_matrix_free (B); 
	gsl_vector_free (gradient); 	

	gsl_vector_free (dx); 
	gsl_vector_free (x_new); 
	gsl_vector_free (gradient_new);

	gsl_vector_free (dgradient); 
	gsl_vector_free (u); 

	fprintf (stderr, "quasi_newton : steps = %i, good steps = %i, bad steps = %i\n", steps, good_steps, bad_steps); 
	fprintf (stderr, "quasi_newton : function value at min %g \n", fx); 

	return steps; 
}
