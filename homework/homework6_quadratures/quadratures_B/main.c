#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>
#include "integrate.h"

void integral_comparison()
{
	double min = 0, max = 1; 
	double acc = 1e-3, eps = 1e-3;

	int calls = 0; 

	double f (double x) 
	{
		calls++; 
		return 1/sqrt(x); 
	}

	double RIA_of_f = integrate (f, min, max, acc, eps); 
	int RIA_calls = calls; calls = 0; 	

	double CC_of_f = clenshaw_curtis (f, min, max, acc, eps); 	
	int CC_calls = calls; calls = 0; 

	FILE * out = fopen ("out.txt", "w");

	fprintf (out, "Integral 1/sqrt(t) from 0 to 1: \n");
	fprintf (out, "%g \t %i calls \t (Recursive adaptive integrator) \n", RIA_of_f, RIA_calls);
	fprintf (out, "%g \t %i calls \t (Clenshaw-Curtis) \n", CC_of_f, CC_calls);
	fprintf (out, "%g \t \t \t \t (analytically) \n", 2.0);

	fclose (out); 	
}

void accuracy_comparison()
{
	double min = 0, max = 1; 
	double eps = 0; 

	int calls = 0; 

	double f (double x)
	{
		calls++; 
		return 4.0*sqrt(1.0 - x*x);
	}

	int calls_gsl = 0; 

	double f_gsl (double x, void * params)
	{
		calls_gsl++;

		double a = * (double *) params; 
		return a*sqrt(1.0 - x*x); 
	}

	double a = 4.0; 

	gsl_function F; 
	F.function = &f_gsl; 
	F.params = &a;

	gsl_integration_workspace * w = gsl_integration_workspace_alloc (1000); 
	double result, error; 

	FILE * data_RIA = fopen ("data_RIA.txt", "w"); 
	FILE * data_CC = fopen ("data_CC.txt", "w"); 
	FILE * data_gsl = fopen ("data_gsl.txt", "w"); 

	for (double acc = 1.0; acc > 1e-11; acc *= 0.1)
	{
		calls = 0; 
		double RIA = integrate (f, min, max, acc, eps);
		fprintf (data_RIA, "%i %g \n", calls, fabs (M_PI - RIA));  

		calls = 0; 
		double CC = clenshaw_curtis (f, min, max, acc, eps); 
		fprintf (data_CC, "%i %g \n", calls, fabs (M_PI - CC)); 

		calls_gsl = 0;
		gsl_integration_qag (&F, min, max, acc, eps, 1000, 6, w, &result, &error); 
		fprintf (data_gsl, "%i %g \n", calls_gsl, fabs (M_PI - result)); 	
			
	}

	fclose (data_RIA);
	fclose (data_CC);
	fclose (data_gsl); 
}

int main()
{
	integral_comparison(); 
	accuracy_comparison();



	return 0; 
}
