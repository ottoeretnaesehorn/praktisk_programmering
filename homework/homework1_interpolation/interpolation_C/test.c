#include <stdio.h> 
#include <stdlib.h>
#include "cubic_spline.h"
#include <gsl/gsl_interp.h>

void create_and_print_points (int n, double x[], double y[]) 
{
	FILE * points = fopen ("./points.txt", "w"); 

	for (int i = 0; i < n; i++)
	{
		x[i] = i + 1.0; 
		y[i] = i + 1.0; 

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

	cubic_spline * spline = cubic_spline_alloc (n, x, y);
	
	gsl_interp * gsl_spline = gsl_interp_alloc (gsl_interp_cspline, n);
	gsl_interp_init (gsl_spline, x, y, n);

	double inc = 1./16;

	for (double z = x[0]; z <= x[n - 1]; z += inc)
	{
		fprintf (spline_data, 
				"%10g %10g %10g %10g %10g %10g %10g \n",
				z, 
				cubic_spline_eval (spline, z),
				gsl_interp_eval (gsl_spline, x, y, z, NULL),
				cubic_spline_integ (spline, z),
				gsl_interp_eval_integ (gsl_spline, x, y, x[0], z, NULL), 
				cubic_spline_deriv (spline, z),
				gsl_interp_eval_deriv (gsl_spline, x, y, z, NULL)); 
	}

	cubic_spline_free (spline);
	gsl_interp_free (gsl_spline);
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
