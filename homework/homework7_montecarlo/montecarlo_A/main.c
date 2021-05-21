#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "monte_carlo_plain.h"

int main()
{
	double f (double * t)
	{
		return 1./(1. - cos(t[0])*cos(t[1])*cos(t[2]))/M_PI/M_PI/M_PI;
	}

	double a[] = {0, 0, 0};
	double b[] = {M_PI, M_PI, M_PI}; 

	int N = 1e7;

	complex result = monte_carlo_plain (3, f, a, b, N); 

	printf ("Integral over (1 - cos(x)cos(y)cos(z))^-1:\n");
	printf ("result = %g +/- %g \t (Monte Carlo) \n", creal(result), cimag(result));
	printf ("result = %g \t \t \t (Analytic) \n", pow(tgamma(1./4), 4)/4/M_PI/M_PI/M_PI);

	return 0; 
}
