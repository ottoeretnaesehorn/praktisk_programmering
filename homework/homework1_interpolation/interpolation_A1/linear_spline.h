#include <assert.h>
#include "binary_search.h"
#include "value_check.h"

double linear_spline (int n, double x[], double y[], double z)
{
	value_check (n, x, z); 

	int i = binary_search (n, x, y, z); 	

	double dx = x[i + 1] - x[i]; 
	double dy = y[i + 1] - y[i]; 

	assert (dx > 0); 

	return y[i] + dy/dx*(z - x[i]); 
}

double anti_derivative (int i, double x[], double y[], double z)
{
	double dx = x[i + 1] - x[i]; 
	double dy = y[i + 1] - y[i]; 

	assert (dx > 0); 
	
	return (z - x[i])*(y[i] + dy/dx*(z - x[i])/2); 
}

double linear_spline_integ (int n, double x[], double y[], double z_0,  double z)
{
	value_check (n, x, z); 

	int i = binary_search (n, x, y, z); 	
	int j = binary_search (n, x, y, z_0);

	double integral = linear_anti_derivative (i, x, y, z) - linear_anti_derivative (i, x, y, x[i]);
	i--;

	while (i >= j)
	{
		integral += linear_anti_derivative (i, x, y, x[i + 1]) - linear_anti_derivative (i, x, y, x[i]);
		i--;
	}


	return integral;
}
