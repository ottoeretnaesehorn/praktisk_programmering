#include <stdio.h> 
#include <stdlib.h>
#include "quadratic_spline.h"
#include <gsl/gsl_interp.h>

int main() 
{
	int n = 10; 

	double x[n]; 
	double y[n]; 

	FILE * points = fopen ("./points.txt", "w"); 

	for (int i = 0; i < n; i++)
	{
		x[i] = i + 1.0; 
		y[i] = (double) 10*rand()/RAND_MAX; 

		fprintf (points, "%10g %10g\n", x[i], y[i]); 
	}

	fclose (points);

	FILE * spline = fopen ("./spline.txt", "w");

	quadratic_spline quadratic = quadratic_spline_alloc (n, x, y);

	gsl_interp * linear = gsl_interp_alloc (gsl_interp_linear, n); 
	gsl_interp_init (linear, x, y, n); 
	
	double inc = 1./16;

	for (double z = x[0]; z <= x[n - 1]; z += inc)
	{
		fprintf (spline, "%10g %10g %10g \n", 
				z, 
				linear_spline (n, x, y, z), 
				gsl_interp_eval(linear, x, y, z, NULL));
	}

	fclose (spline); 
	
	FILE * spline_integrated = fopen ("./spline_integrated.txt", "w");

	for (double z = x[0]; z <= x[n - 1]; z += inc)
	{
		fprintf (spline, "%10g %10g %10g \n", 
				z, 
				linear_spline_integrator (n, x, y, x[0], z), 
				gsl_interp_eval_integ(linear, x, y, x[0], z, NULL));
	}

	fclose (spline_integrated); 

	gsl_interp_free (linear); 

	return 0; 
}
