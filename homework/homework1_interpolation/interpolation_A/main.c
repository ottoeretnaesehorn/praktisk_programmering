#include <stdio.h> 
#include <stdlib.h>
#include "linear_spline.h"
#include <gsl/gsl_interp.h>

void create_and_print_points (int n, double x[], double y[])
{
	FILE * points = fopen ("./points.txt", "w"); 

	for (int i = 0; i < n; i++)
	{
		x[i] = i + 1.0; 
		y[i] = (double) 10*rand()/RAND_MAX; 

		fprintf (points, "%10g %10g\n", x[i], y[i]); 
	}

	fclose (points);
}

void create_and_print_spline (int n, double x[], double y[])
{
	FILE * data = fopen ("./data.txt", "w");

	gsl_interp * gsl_linear = gsl_interp_alloc (gsl_interp_linear, n); 
	gsl_interp_init (gsl_linear, x, y, n); 
	
	double inc = 1./16;

	for (double z = x[0]; z < x[n - 1]; z += inc)
	{
		fprintf (data, "%10g %10g %10g %10g %10g \n", 
				z, 
				linear_spline (n, x, y, z), 
				gsl_interp_eval(gsl_linear, x, y, z, NULL),
				linear_spline_integ (n, x, y, x[0], z), 
				gsl_interp_eval_integ(gsl_linear, x, y, x[0], z, NULL));
	}

	gsl_interp_free (gsl_linear);
	fclose (data); 
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

