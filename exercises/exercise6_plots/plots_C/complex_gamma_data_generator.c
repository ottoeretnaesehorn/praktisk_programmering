#include <stdio.h>
#include <math.h>
#include <complex.h>

complex complex_gamma(complex z)
{
	// Single precision gamma function (Gergo Nemes, from Wikipedia)

	double PI = 3.14159265359; 
	
	if (creal(z) < 0) 
	{
		return PI/csin(PI*z)/complex_gamma(1 - z);
	}
	
	if (creal(z) < 9)
	{
		return complex_gamma(z + 1)/z; 
	}

	complex ln_complex_gamma = z*clog(z + 1.0/(12.0*z - 1.0/z/10)) - z + clog(2*PI/z)/2;

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
			printf("%10g %10g %10g \n", x, y, cabs(complex_gamma(x + I*y)));
		}
	}

	return 0;
}
