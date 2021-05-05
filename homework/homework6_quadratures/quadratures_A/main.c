#include <stdio.h>
#include <math.h>
#include "integrate.h"

int main()
{
	double min = 0, max = 1; 
	double acc = 1e-3, eps = 1e-3;
	
	double f (double t) 
	{
		return sqrt(t); 
	}

	double integral_of_f = integrate (f, min, max, acc, eps); 	

	printf ("Integral sqrt(t) from 0 to 1: \n");
	printf ("%g \t (from rutine) \n", integral_of_f);
	printf ("%g \t (analytically) \n", 2./3);

	double g (double x)
	{
		return 4*sqrt(1 - x*x); 
	}

	double integral_of_g = integrate (g, min, max, acc, eps);

	printf ("\nIntegral of 4*sqrt(1 - x^2) from 0 to 1: \n");
	printf ("%g \t (from rutine) \n", integral_of_g);
	printf ("%g \t (analytically) \n", M_PI); 
	
	return 0; 
}
