#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "monte_carlo_strata.h"

#define RANDOM (double) rand()/RAND_MAX

double monte_carlo_strata (
		int dim, 
		double f (double * x), 
		double * a, 
		double * b, 
		double acc,
		double eps, 
		double n_reuse, 
		double mean_reuse
		)
{
	int N = 16*dim; 
	double V = 1.; 

	for (int i = 0; i < dim; i++)
	{
		V *= b[i] - a[i]; 
	}

	double x[dim]; 
	double mean_left[dim], mean_right[dim], mean = 0.; 
	int n_left[dim], n_right[dim]; 

	for (int i = 0; i < dim; i++)
	{
		mean_left[i] = 0.;  
		mean_right[i] = 0.;
		
	       	n_left[i] = 0; 
		n_right[i] = 0;
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			x[j] = a[j] + RANDOM*(b[j] - a[j]); 
		}

		double fx = f(x); 

		for (int j = 0; j < dim; j++)
		{
			if (x[j] > (a[j] + b[j])/2)
			{
				n_right[j]++; 
				mean_right[j] += fx;
			}	
			else 
			{
				n_left[j]++;
				mean_left[j] += fx; 
			}
		}

		mean += fx;
	}
	
	mean /= N; 
	
	for (int i = 0; i < dim; i++)
	{
		mean_left[i] /= n_left[i];
		mean_right[i] /= n_right[i];
	}	

	double max_variance = 0.;
	int index_at_max = 0;

	for (int i = 0; i < dim; i++)
	{
		double variance = fabs (mean_right[i] - mean_left[i]); 

		if (variance > max_variance)
		{
			max_variance = variance; 
			index_at_max = i; 
		}
	}	

	double integral = (N*mean + mean_reuse*n_reuse)/(N + n_reuse)*V;
	double error = fabs (mean_reuse - mean)*V;

	double tolerance = acc + fabs (integral)*eps; 

	if (error < tolerance)
	{
		return integral;
	}

	double a_new[dim], b_new[dim];

	for (int i = 0; i < dim; i++)
	{
		a_new[i] = a[i]; 
		b_new[i] = b[i]; 
	}

	a_new[index_at_max] = (a[index_at_max] + b[index_at_max])/2;
	b_new[index_at_max] = (a[index_at_max] + b[index_at_max])/2;


	double integral_left = monte_carlo_strata (
			dim, 
			f, 
			a, 
			b_new, 
			acc/sqrt(2.), 
			eps, 
			n_left[index_at_max], 
			mean_left[index_at_max]); 

	double integral_right = monte_carlo_strata (
			dim, 
			f, 
			a_new, 
			b, 
			acc/sqrt(2.), 
			eps, 
			n_right[index_at_max], 
			mean_right[index_at_max]); 

	return integral_left + integral_right; 

}
