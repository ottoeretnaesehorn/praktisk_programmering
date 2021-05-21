#include <stdio.h>
#include <math.h>
#include <gsl/gsl_vector.h>
#include "quasi_newton.h"
#include "neuralnetwork.h"

NN * NN_alloc (int n, 
		double (* function) (double t),
		double (* derivative) (double t),
		double (* integral) (double t))
{
	NN * network = malloc (sizeof (NN)); 

	network->n = n; 
	network->function = function; 
	network->derivative = derivative; 
	network->integral = integral; 
	network->parameters = gsl_vector_alloc (3*n);

	return network;	
}	

void NN_free (NN * network)
{
	gsl_vector_free (network->parameters); 
	free (network); 
}

double NN_response (NN * network, double x)
{
	double sum = 0; 

	for (int i = 0; i < network->n; i++)
	{
		double a = gsl_vector_get (network->parameters, 3*i + 0); 
		double b = gsl_vector_get (network->parameters, 3*i + 1); 
		double w = gsl_vector_get (network->parameters, 3*i + 2); 

		sum += network->function((x - a)/b)*w;
	}

	return sum; 
}

double NN_derivative (NN * network, double x)
{
	double sum = 0; 

	for (int i = 0; i < network->n; i++)
	{
		double a = gsl_vector_get (network->parameters, 3*i + 0); 
		double b = gsl_vector_get (network->parameters, 3*i + 1); 
		double w = gsl_vector_get (network->parameters, 3*i + 2); 

		sum += network->derivative((x - a)/b)*w;
	}

	return sum; 
}

double NN_integral (NN * network, double x)
{
	double sum = 0; 

	for (int i = 0; i < network->n; i++)
	{
		double a = gsl_vector_get (network->parameters, 3*i + 0); 
		double b = gsl_vector_get (network->parameters, 3*i + 1); 
		double w = gsl_vector_get (network->parameters, 3*i + 2); 

		sum += network->integral((x - a)/b)*w;
	}

	return sum; 
}

void NN_train (NN * network, gsl_vector * x, gsl_vector * y)
{
	double cost_function (gsl_vector * parameters)
	{
		gsl_vector_memcpy (network->parameters, parameters);
		double sum = 0; 

		for (int i = 0; i < x->size; i++)
		{
			double x_i = gsl_vector_get (x, i); 
			double y_i = gsl_vector_get (y, i); 
			double f_i = NN_response (network, x_i); 

			sum += (f_i - y_i)*(f_i - y_i);  
		}
	
		return sum/x->size; 
	}

	gsl_vector * parameters = gsl_vector_alloc (network->parameters->size); 
	gsl_vector_memcpy (parameters, network->parameters);

	quasi_newton (cost_function, network->parameters, 1e-3); 
	gsl_vector_memcpy (parameters, network->parameters);
		
	gsl_vector_free (parameters);
}
