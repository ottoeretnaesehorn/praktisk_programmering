#include <stdio.h>
#include <math.h>
#include <complex.h>

double E = exp(1);
double PI = 3.1415926535897932384;



void gamma_check()
{
	double gamma_of_5 = exp(gamma(5));
	printf("gamma(5) = %g\n", gamma_of_5);
}

void bessel_check()
{
	double first_order_bessel = j1(0.5);
	printf("j1(0.5) = %g\n", first_order_bessel);
}



int main() 
{
	printf("Checking functions from math.h:\n");	
	gamma_check();
	bessel_check();
	
	printf("\nChecking functions from complex.h:\n");
	printf("sqrt(-2) = %g + I*%g\n", creal(csqrt(-2)), cimag(csqrt(-2)));
	printf("exp(I*PI) = %g + I*%g\n", creal(cexp(I*PI)), cimag(cexp(I*PI)));
	printf("exp(I) = %g + I*%g\n", creal(cexp(I)), cimag(cexp(I)));
	printf("I^e = %g + I*%g\n", creal(cpow(I, E)), cimag(cpow(I, E)));
	printf("I^I = %g + I*%g\n", creal(cpow(I, I)), cimag(cpow(I, I)));

	return 0;
}


