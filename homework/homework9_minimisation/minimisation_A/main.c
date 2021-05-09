#include <stdio.h>
#include <gsl/gsl_vector.h>
#include "quasi_newton.h"
#include "printing.h"

int main()
{
	double rosenbrock (gsl_vector * x)
	{
		double x0 = gsl_vector_get (x, 0);
		double x1 = gsl_vector_get (x, 1); 

		return (1. - x0)*(1. - x0) + 100.*(x1 - x0*x0)*(x1 - x0*x0);
	}
	double himmelblau (gsl_vector * x)
	{
		double x0 = gsl_vector_get (x, 0); 
		double x1 = gsl_vector_get (x, 1); 

		return (x0*x0 + x1 - 11.)*(x0*x0 + x1 - 11.) + (x0 + x1*x1 - 7.)*(x0 + x1*x1 - 7.); 
	}

	gsl_vector * rosenbrock_min = gsl_vector_alloc (2); 
	gsl_vector * himmelblau_min = gsl_vector_alloc (2); 

	for (int i = 0; i < rosenbrock_min->size; i++)
	{
		gsl_vector_set (rosenbrock_min, i, 0.01); 
		gsl_vector_set (himmelblau_min, i, 0.01); 
	}

	double eps = 1e-5; 

	int steps_rosenbrock = quasi_newton (rosenbrock, rosenbrock_min, eps); 
	int steps_himmelblau = quasi_newton (himmelblau, himmelblau_min, eps); 

	print_vector ("Min of Rosenbrocks function found at ", rosenbrock_min); 
	printf ("Algorithm used %i steps \n \n", steps_rosenbrock); 

	print_vector ("Min of Himmelblau function found at ", himmelblau_min); 
	printf ("Algorithm used %i steps \n", steps_himmelblau); 

	return 0; 
}
