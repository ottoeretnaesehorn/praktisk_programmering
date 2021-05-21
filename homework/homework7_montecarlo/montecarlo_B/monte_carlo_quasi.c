#include <assert.h>
#include <complex.h>
#include <math.h>
#include "monte_carlo_quasi.h"

double corput (int n, int base)
{
	double q = 0; 
	double bk = (double) 1./base; 

	while (n > 0)
	{
		q += (n % base)*bk; 
		n /= base; 
		bk /= base;
	}

	return q; 
}

void halton1 (int n, int d, double * a, double * b, double * x)
{
	int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 47, 53, 59, 61, 67, 71, 73, 79};

	int d_max = sizeof (base)/sizeof (int);
	assert (d <= d_max);

	for (int i = 0; i < d; i++)
	{
		x[i] = corput (n, base[i]); 
	}
}

void halton2 (int n, int d, double * a, double * b, double * x)
{
	int base[] = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 47, 53, 59, 61, 67, 71, 73, 79, 83};

	int d_max = sizeof (base)/sizeof (int);
	assert (d <= d_max);

	for (int i = 0; i < d; i++)
	{
		x[i] = corput (n, base[i]); 
	}
}

complex monte_carlo_quasi (int d, double f (double * x), double a[], double b[], int N)
{
	double x[d]; 
	double V = 1; 

	for (int i = 0; i < d; i++)
	{
		V *= b[i] - a[i];
	}

	double sum1 = 0, sum2 = 0;

	for (int i = 0; i < N/2; i++)
	{
		halton1 (i, d, a, b, x); 
		sum1 += f(x); 
	}

	for (int i = 0; i < N/2; i++)
	{
		halton2 (i, d, a, b, x);
		sum2 += f(x);
	}

	double integral = (sum1 + sum2)/N*V;
	double error = fabs (sum1 - sum2)/N*V;

	return integral + I*error;
}	

