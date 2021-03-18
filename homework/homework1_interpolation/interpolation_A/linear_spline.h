#include <assert.h>
#include "binary_search.h"

double linear_spline (int n, double x[], double y[], double z)
{
	assert (n > 1 && z >= x[0] && z <= x[n - 1]); 

	int i = binary_search (n, x, y, z); 	

	double dx = x[i + 1] - x[i]; 
	double dy = y[i + 1] - y[i]; 

	assert (dx > 0); 

	return y[i] + dy/dx*(z - x[i]); 
}

double linear_anti_derivative (int i, double x[], double y[], double z)
{
	double dx = x[i + 1] - x[i]; 
	double dy = y[i + 1] - y[i]; 

	assert (dx > 0); 
	
	return (z - x[i])*(y[i] + dy/dx*(z - x[i])/2); 
}

double linear_spline_integrator (int n, double x[], double y[], double z_0,  double z)
{
	assert (n > 1 && z >= x[0] && z <= x[n - 1]); 

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
