#include <stdio.h>
#include <math.h>
#include <gsl/gsl_sf_erf.h>

double single_precision_erf(double x)
{
	// Single precision error function (Abramowitz and Stegun, from Wikipedia)

	double a[] = {0.254829592, -0.284496736, 1.421413741, -1.453152027, 1.061405429};
	double t = 1.0/(1 + 0.3275911*x);

	if (x < 0) 
	{
		return -single_precision_erf(-x); 
	}

	double sum = t*(a[0] + t*(a[1] + t*(a[2] + t*(a[3] + t*a[4]))));

	return 1.0 - sum*exp(-x*x);
}

int main()
{
	double min = -2; 
	double max = 2; 
	double inc = 1.0/8; 

	for (double x = min; x <= max; x += inc)
	{
		printf("%10g %10g %10g %10g \n", x, erf(x), gsl_sf_erf(x), single_precision_erf(x));
	}

	return 0;
}
