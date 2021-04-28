#include <stdio.h> 
#include <stdlib.h>
#include "quadratic_spline.h"
#include <gsl/gsl_interp.h>

void create_and_print_points (int n, double x[], double y[]) 
{
	FILE * points = fopen ("./points.txt", "w"); 

	for (int i = 0; i < n; i++)
	{
		x[i] = i + 1.0; 
		y[i] = (double) 10*rand()/RAND_MAX; 

		fprintf (points, 
				"%10g %10g \n", 
				x[i], 
				y[i]); 
	}

	fclose (points);
}

void create_and_print_spline (int n, double x[], double y[])
{
	FILE * spline_data = fopen ("./spline_data.txt", "w");

	quadratic_spline * spline = quadratic_spline_alloc (n, x, y);

	double inc = 1./16;

	for (double z = x[0]; z <= x[n - 1]; z += inc)
	{
		fprintf (spline_data, 
				"%10g %10g %10g %10g \n", 
				z, 
				quadratic_spline_eval (spline, z), 
				quadratic_spline_integ (spline, spline->x[0], z),
				quadratic_spline_deriv (spline, z));
	}

	quadratic_spline_free (spline);
	fclose (spline_data); 
}

int main() 
{
	int n = 10; 

	double x[n]; 
	double y[n]; 

	create_and_print_points (n, x, y); 
	create_and_print_spline (n, x, y);

	return 0;
}
