#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ode_rk12.h"

void f (double t, double y[], double dydt[])
{
	dydt[0] = y[1];
	dydt[1] = -y[0];
}

int main () 
{
	int n = 2;  

	double a = 0.0; 
	double b = 6.0;
	double y[] = {1, 0};

	double h = 0.2; 
	double acc = 1e-2; 
	double eps = 1e-2;

	driver_rk12 (n, f, a, b, y, h, acc, eps, stdout); 

	return 0; 
}
