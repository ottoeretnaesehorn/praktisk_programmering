#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define FORALL(i) for (int i = 0; i < n; i++) 

void runge_kutta_23 (
		int n, 
		double t, 
		double y[], 
		void f (double t, double y[], double dydt[]),
		double h, 
		double step[], 
		double dy[]
		)
{
	double k0[n]; 
	f (t, y, k0); 

	double y1[n]; 
	FORALL(i) y1[i] = y[i] + (1./2*h)*k0[i]; 
	
	double k1[n]; 
	f (t + 1./2*h, y1, k1);

	double y2[n]; 
	FORALL(i) y2[i] = y[i] + (3./4*h)*k1[i];	

	double k2[n]; 
	f (t + 3./4*h, y2, k2);

	double ka[n];
	FORALL(i) ka[i] = (2*k0[i] + 3*k1[i] + 4*k2[n])/9;

	FORALL(i) step[i] = y[i] + h*ka[i];
	FORALL(i) dy[i] = (ka[i] - k1[i])*h;
}

void print_path (FILE * path, int n, double t, double y[])
{
	fprintf (path, "%g ", t);
	FORALL(i) fprintf (path, "%g ", y[i]); 
	fprintf (path, "\n"); 
}

void ode_driver (
		int n, 
		void f (double t, double y[], double dydt[]),
		double a, 
		double b, 
		double y[],
		double h,
		double acc, 
		double eps,
		FILE * path
		)
{
		double t = a; 
		print_path (path, n, t, y); 

		while (t < b)
		{
			if (t + h > b)
			{
				h = b - t;
			}

			double steps[n], dy[n];
			runge_kutta_23 (n, t, y, f, h, steps, dy);

			double sum = 0; 
			FORALL(i) sum += y[i]*y[i];

			double norm_y = sqrt(sum);

			sum = 0;
			FORALL(i) sum += dy[i]*dy[i];

			double err = sqrt(sum); 
			double tol = (acc + eps*norm_y)*sqrt(h/(b - a));

			if (err < tol)
			{
				t = t + h; 
				FORALL(i) y[i] = steps[i];
				
				print_path (path, n, t, y);
			}

			if (err > 0)
			{
				h *= 0.95*pow(tol/err, 0.25); 
			}
			else 
			{
				h *= 2;
			}
		}
}
