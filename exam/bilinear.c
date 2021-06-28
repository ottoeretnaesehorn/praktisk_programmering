#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include "bilinear.h"

int binary_search (gsl_vector * z, double dz)
{
	assert (dz >= gsl_vector_get (z, 0) && dz <= gsl_vector_get (z, z->size - 1));
	
	int i = 0, j = z->size - 1;

	while (j - i > 1)
	{
		int m  = (i + j)/2; 

		if (dz > gsl_vector_get (z, m))
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

double bilinear (
		gsl_vector * x, 
		gsl_vector * y, 
		gsl_matrix * F, 
		double dx, 
		double dy
		)
{
	// Indicies of the quadrant 
	int nx = binary_search (x, dx), ny = binary_search (y, dy);

	// Corners of the quadrant 
	double x1 = gsl_vector_get (x, nx), x2 = gsl_vector_get (x, nx + 1); 
	double y1 = gsl_vector_get (y, ny), y2 = gsl_vector_get (y, ny + 1); 

	// Function values in the corners
	double F11 = gsl_matrix_get (F, nx, ny), F12 = gsl_matrix_get (F, nx, ny + 1);
	double F21 = gsl_matrix_get (F, nx + 1, ny), F22 = gsl_matrix_get (F, nx + 1, ny + 1);

	// Solutions to the linear equation
	double factor = (x1 - x2)*(y1 - y2);
	double a = (F11*x2*y2 - F12*x2*y1 - F21*x1*y2 + F22*x1*y1)/factor;
	double b = (- F11*y2 + F12*y1 + F21*y2 - F22*y1)/factor;
	double c = (- F11*x2 + F12*x2 + F21*x1 - F22*x1)/factor;
	double d = (F11 - F12 - F21 + F22)/factor;
	
	return a + b*dx + c*dy + d*dx*dy;
}
