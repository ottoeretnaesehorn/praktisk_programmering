#include <stdio.h>
#include <math.h>
#include "monte_carlo_strata.h"

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
	double acc = 0.1;
	double eps = 0.1; 
	
	double f2 (double * x) 
	{
		return S_n (2, x);
	}
	double a2[] = {-1, -1};
	double b2[] = {1, 1}; 

	double result2 = monte_carlo_strata (2, f2, a2, b2, acc, eps, 0, 0); 

	printf ("Area of circle:\n");
	printf ("result = %g +/- %g \n", result2, acc + fabs (result2)*eps);
	printf ("result = %g \n\n", M_PI);
	
	double f3 (double * x) 
	{
		return S_n (3, x);
	}
	double a3[] = {-1, -1, -1};
	double b3[] = {1, 1, 1}; 

	double result3 = monte_carlo_strata (3, f3, a3, b3, acc, eps, 0, 0); 

	printf ("Volume of sphere:\n");
	printf ("result = %g +/- %g \n", result3, acc + fabs (result3)*eps);
	printf ("result = %g \n", 4./3.*M_PI);

	return 0; 
}
