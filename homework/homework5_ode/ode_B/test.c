#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "runge_kutta.h"

void f (double t, double y[], double dydt[])
{
	dydt[0] = 1;
//	dydt[1] = -y[0];
}

int main () 
{
	int n = 1;  

	double a = 0.0; 
	double b = 6.0;
	double y[] = {0};

	double h = 0.2; 
	double acc = 1e-2; 
	double eps = 1e-2;

	ode_driver (n, f, a, b, y, h, acc, eps, stdout); 


	return 0; 
}
