#include <stdio.h>
#include <math.h>
#include <gsl/gsl_sf_gamma.h>

double stirling_approximation_lngamma(double x)
{
	// Single precision lngamma function (Gergo Nemes, from Wikipedia)

	double PI = 3.14159265359; 
	
	if (x < 0) 
	{
		return log(PI) - log(fabs(sin(PI*x))) - stirling_approximation_lngamma(1.0 - x);
	}
	
	if (x < 9)
	{
		return stirling_approximation_lngamma(x + 1.0) - log(x); 
	}

	return x*log(x + 1.0/(12*x - 1.0/x/10)) - x + log(2*PI/x)/2.0;
}

int main()
{
	double min = -5.01; 
	double max = 5.01; 
	double inc = 1.0/8; 

	for (double x = min; x <= max; x += inc)
	{
		printf("%10g %10g %10g %10g \n", x, gamma(x), gsl_sf_lngamma(x), stirling_approximation_lngamma(x));
	}

	return 0;
}
