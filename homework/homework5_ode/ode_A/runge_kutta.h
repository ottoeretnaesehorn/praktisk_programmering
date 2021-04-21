#include <math.h>

void runge_kutta_23 (
		int n, 
		double t, 
		double y[], 
		void f (double t, double y[], double dydt[]),
		double h, 
		double full_step[], 
		double dy[]
		)
{
	double k1[n], k2[n], k3[n], k4[n];
	double two_partial_steps[n];

	f (t, y, k1); 

	for (int i = 0; i < n; i++)
	{
		two_partial_steps[i] = y[i] + 1./2*k1[i]*h;
	}

	f (t + 1./2*h, two_partial_steps, k2); 

	for (int i = 0; i < n; i++)
	{
		two_partial_steps[i] = y[i] + 3./4*k2[i]*h;
	}

	f (t + 3./4*h, two_partial_steps, k3); 

	for (int i = 0; i < n; i++) 
	{
		full_step[i] = y[i] + (2./9*k1[i] + 1./3*k2[i] + 4./9*k3[i])*h;
	}

	f (t + h, full_step, k4); 

	for (int i = 0; i < n; i++)
	{
		full_step[i] = y[i] + (7./24*k1[i] + 1./4*k2[i] + 1./3*k3[i] + 1./8*k4[i])*h;
		dy [i] = full_step[i] - two_partial_steps[i]; 
	}
}

void ode_driver (
		int n, 
		void f (double t, double y[], double dydt[]),
		double a, 
		double b, 
		double y[],
		double h, 
		double acc, 
		double eps)
{
		double t = a; 

		while (t < b)
		{
			if (t + h > b)
			{
				h = b - t;
			}

			double steps[n];
			double dy[n];

			runge_kutta_23 (n, t, y, f, h, steps, dy);

			double sum = 0; 

			for (int i = 0; i < n; i++)
			{
				sum += y[i]*y[i];
			}

			double norm_y = sqrt(sum);

			sum = 0;

			for (int i = 0; i < n; i++)
			{
				sum += dy[i]*dy[i];
			}

			double err = sqrt(sum); 
			double tol = (acc + eps*norm_y)*sqrt(h/(b - a));

			if (err < tol)
			{
				t = t + h; 

				for (int i = 0; i < n; i++)
				{
					y[i] = steps[i];
				}
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
