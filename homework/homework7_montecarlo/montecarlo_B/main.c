#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "monte_carlo_quasi.h"

double S_n (int n, double * x)
{
	double surface = 0; 

	for (int i = 0; i < n; i++)
	{
		surface += x[i]*x[i];
	}

	if (surface <= 1)
	{
		return 1.;
	}
	else 
	{
		return 0.;
	}
}

int main()
{
	int N = 1e5;
	
	double f2 (double * x) 
	{
		return S_n (2, x);
	}
	double a2[] = {-1, -1};
	double b2[] = {1, 1}; 

	complex result2 = monte_carlo_quasi (2, f2, a2, b2, N); 

	printf ("Area of circle:\n");
	printf ("result = %g +/- %g \n", creal(result2), cimag(result2));
	printf ("result = %g \n\n", M_PI);
	
	double f3 (double * x) 
	{
		return S_n (3, x);
	}
	double a3[] = {-1, -1, -1};
	double b3[] = {1, 1, 1}; 

	complex result3 = monte_carlo_quasi (3, f3, a3, b3, N); 

	printf ("Volume of sphere:\n");
	printf ("result = %g +/- %g \n", creal(result3), cimag(result3));
	printf ("result = %g \n", 4./3.*M_PI);

	return 0; 
}
