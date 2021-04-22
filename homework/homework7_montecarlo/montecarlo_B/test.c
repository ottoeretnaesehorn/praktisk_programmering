#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "monte_carlo.h"

int main()
{
	double f (double * t)
	{
		return 1./(1. - cos(t[0])*cos(t[1])*cos(t[2]));
	}

	double a[] = {0, 0, 0};
	double b[] = {M_PI, M_PI, M_PI}; 

	int N = 1e7;

	complex result = plain_monte_carlo (3, f, a, b, N); 

	printf ("result = %g +/- %g \n", creal(result), cimag(result));
	printf ("result = %g \n", pow(tgamma(1./4), 4)/4);

	return 0; 
}
