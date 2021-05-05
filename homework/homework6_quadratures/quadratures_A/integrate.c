#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "integrate.h"

double abcissa[] = {1./6, 2./6, 4./6, 5./6};
double higher_order_weight[] = {2./6, 1./6, 1./6, 2./6};
double lower_order_weight[] = {1./4, 1./4, 1./4, 1./4};

double adapt (
		double f (double t), 
		double min, 
		double max, 
		double acc, 
		double eps, 
		double f1,
	       	double f2,	
		int recursions
	     )
{
	assert (recursions < 1e6);
	
	double f0 = f (min + (max - min)*abcissa[0]);
	double f3 = f (min + (max - min)*abcissa[3]);

	double higher_order = (max - min)
		*(higher_order_weight[0]*f0
		+ higher_order_weight[1]*f1
		+ higher_order_weight[2]*f2
		+ higher_order_weight[3]*f3);

	double lower_order = (max - min) 
		*(lower_order_weight[0]*f0
		+ lower_order_weight[1]*f1
		+ lower_order_weight[2]*f2
		+ lower_order_weight[3]*f3);

	double tolerance = acc + eps*fabs(higher_order);
	double error = fabs (higher_order - lower_order); 

	if (error < tolerance)
	{	
		return higher_order;
	}
	else 
	{
		double step1 = adapt (f, min, (max + min)/2.0, acc/sqrt(2.), eps, f0, f1, recursions + 1); 
		double step2 = adapt (f, (max + min)/2.0, max, acc/sqrt(2.), eps, f2, f3, recursions + 1); 	
	
		return step1 + step2;
	}
}

double integrate(
		double f (double t), 
		double min, 
		double max, 
		double acc, 
		double eps
		)
{
	double f1 = f (min + (max - min)*abcissa[1]); 
	double f2 = f (min + (max - min)*abcissa[2]);

	int recursions = 0; 

	return adapt (f, min, max, acc, eps, f1, f2, recursions); 
}
