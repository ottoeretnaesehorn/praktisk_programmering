#include <stdio.h>
#include <math.h>
#include "integrate.h"

int main()
{
	int calls = 0; 

	double min = 0, max = 1; 
	double acc = 1e-2, eps = 1e-2;

	double f (double t) 
	{
		calls++; 

		return sqrt(t); 
	}

	double integral_of_f = integrate (f, min, max, acc, eps); 	

	printf ("Integral sqrt(t) from 0 to 1: \n");
	printf ("%g \t (from rutine) \n", integral_of_f);
	printf ("%g \t (analytically) \n", 2./3);

	printf ("calls = %i \n", calls);
	return 0; 
}
