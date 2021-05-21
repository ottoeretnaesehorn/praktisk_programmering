#include <stdio.h>
#include <math.h>
#include <gsl/gsl_vector.h>
#include "newton.h"
#include "printing.h"

int main()
{
	void rosenbrock_gradient (gsl_vector * x, gsl_vector * fx)
	{
		double x0 = gsl_vector_get (x, 0);
		double x1 = gsl_vector_get (x, 1);  

		gsl_vector_set (fx, 0, -2.*(1 - x0) + 2.*100.*(x1 - x0*x0)*(-2.)*x0);
	       	gsl_vector_set (fx, 1, 2.*100.*(x1 - x0*x0)); 	
	}

	gsl_vector * x = gsl_vector_alloc (2); 

	for (int i = 0; i < x->size; i++)
	{
		gsl_vector_set (x, i, 0.); 
	}	

	double eps = 1e-6; 

	int steps = newton (rosenbrock_gradient, x, eps); 

	printf ("Rosenbrocks function: \n");
	print_vector ("Minimum calculated at ", x); 
	printf ("Rutine used %i steps \n", steps); 

	return 0;
}
