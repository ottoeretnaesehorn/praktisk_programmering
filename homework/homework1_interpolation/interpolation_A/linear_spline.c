#include <assert.h>
#include "linear_spline.h"

int check_and_search (int n, double x[], double y[], double z)
{
	assert (z >= x[0] && z <= x[n - 1]);

	int i = 0, j = n - 1; 

	while (j - i > 1)
	{
		int m = (i + j)/2; 

		if (z > x[m])
		{
			i = m;
		}
		else 
		{
			j = m;
		}
	}

	return i; 
}

double linear_spline (int n, double x[], double y[], double z)
{
	int i = check_and_search (n, x, y, z); 	

	double dx = x[i + 1] - x[i]; 
	double dy = y[i + 1] - y[i]; 

	assert (dx > 0); 

	return y[i] + dy/dx*(z - x[i]); 
}

double linear_spline_integ (int n, double x[], double y[], double z0, double z)
{
	int i = check_and_search (n, x, y, z); 	
	int j = check_and_search (n, x, y, z0);


	double anti_derivative (int i, double z)
	{
		double dy = y[i + 1] - y[i]; 
		double dx = x[i + 1] - x[i]; 
		assert (dx > 0); 
		
		double h = z - x[i]; 

		return h*(y[i] + dy/dx*h/2); 
	}	

	double integral = anti_derivative (i, z) - anti_derivative (i, x[i]);  

	while (i > j)
	{
		i--;
		integral += anti_derivative (i, x[i + 1]) - anti_derivative (i, x[i]);
	}

	return integral;
}
