#include <stdio.h>
#include <math.h>
#include <complex.h>

complex complex_gamma(complex z)
{
	// Single precision gamma function (Gergo Nemes, from Wikipedia)

	if (creal(z) < 0) 
	{
		return M_PI/csin(M_PI*z)/complex_gamma(1 - z);
	}
	
	if (creal(z) < 9)
	{
		return complex_gamma(z + 1)/z; 
	}

	complex ln_complex_gamma = z*clog(z + 1.0/(12.0*z - 1.0/z/10)) - z + clog(2*M_PI/z)/2;

	return cexp(ln_complex_gamma);
}

int main()
{
	double min = -5.01; 
	double max = 5.01; 
	double inc = 1.0/32; 

	for (double x = min; x <= max; x += inc)
	{
		for (double y = min; y <= max; y += inc)
		{
			printf("%g \t %g \t %g \n", x, y, cabs(complex_gamma(x + I*y)));
		}

		printf("\n");
	}

	return 0;
}
