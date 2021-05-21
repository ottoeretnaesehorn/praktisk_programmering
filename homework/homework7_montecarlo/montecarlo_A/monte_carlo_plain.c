#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include "monte_carlo_plain.h"

#define RANDOM ((double) rand()/RAND_MAX)

complex monte_carlo_plain (
		int dim, 
		double f (double * x), 
		double * a, 
		double * b, 
		int N
		)
{
	double V = 1; 

	for (int i = 0; i < dim; i++)
	{
		V *= b[i] - a[i]; 
	}

	double sum = 0, sum_squared = 0; 
	double x[dim]; 

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			x[j] = a[j] + RANDOM*(b[j] - a[j]); 
		}
		
		double fx = f(x); 

		sum += fx; 
		sum_squared += fx*fx;
	}

	double mean = sum/N; 
	double sigma = sqrt (sum_squared/N - mean*mean);

	return mean*V + I*sqrt(sigma/N)*V; 
}
