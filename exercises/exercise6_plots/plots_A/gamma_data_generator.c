#include <stdio.h>
#include <math.h>
#include <gsl/gsl_sf_gamma.h>

double stirling_approximation_gamma(double x)
{
	// Single precision gamma function (Gergo Nemes, from Wikipedia)

	double PI = 3.14159265359; 
	
	if (x < 0) 
	{
		return PI/sin(PI*x)/stirling_approximation_gamma(1 - x);
	}
	
	if (x < 9)
	{
		return stirling_approximation_gamma(x + 1)/x; 
	}

	double ln_gamma = x*log(x + 1/(12*x - 1/x/10)) - x + log(2*PI/x)/2;

	return exp(ln_gamma);
}

int main()
{
	double min = -5.01; 
	double max = 5.01; 
	double inc = 1.0/8; 

	for (double x = min; x <= max; x += inc)
	{
		printf("%10g %10g %10g %10g \n", x, tgamma(x), gsl_sf_gamma(x), stirling_approximation_gamma(x));
	}

	return 0;
}
