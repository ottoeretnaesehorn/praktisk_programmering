#include <stdio.h>
#include <math.h>
#include <gsl/gsl_vector.h>
#include "neuralnetwork.h"

double activation_function (double x)
{
	return x*exp (-x*x);
}

double function (double x)
{
	return cos (5*x - 1)*exp(-x*x); 
}

int main ()
{
	int n = 4;

	NN * network = NN_alloc (n, activation_function); 

	double a = -1, b = 1; 
	
	int m = 15; 
	gsl_vector * x = gsl_vector_alloc (m); 
	gsl_vector * y = gsl_vector_alloc (m); 

	for (int i = 0; i < m; i++)
	{
		gsl_vector_set (x, i, a + (b - a)*i/(m - 1)); 
		gsl_vector_set (y, i, function (gsl_vector_get (x, i))); 
	}

	for (int i = 0; i < network->n; i++)
	{
		gsl_vector_set (network->parameters, 3*i + 0, a + (b - a)*i/(network->n - 1));
		gsl_vector_set (network->parameters, 3*i + 1, 1.); 
		gsl_vector_set (network->parameters, 3*i + 2, 1.); 
	}

	NN_train (network, x, y); 

	FILE * points = fopen ("points.txt", "w"); 
	for (int i = 0; i < m; i++)
	{
		fprintf (points, "%g %g \n", gsl_vector_get (x, i), gsl_vector_get (y, i));
	}
	fclose (points); 

	FILE * data = fopen ("data.txt", "w"); 
	for (double z = a; z < b; z += 1./64)
	{
		fprintf (data, "%g %g \n", z, NN_response (network, z)); 
	}


	return 0;
}
