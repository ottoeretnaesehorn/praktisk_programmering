#include <math.h>
#include <gsl/gsl_integration.h>

double f (double t, void * params)
{
	return 2/sqrt(M_PI)*exp(-t*t);
}

double error_function(double z)
{
	gsl_function f_for_integration; 
	f_for_integration.function = &f;
	f_for_integration.params = 0;

	int max_iterations = 999; 
	int key = 4; 
	
	gsl_integration_workspace* workspace = gsl_integration_workspace_alloc(max_iterations);
	
	double acc = 1e-6, eps = 1e-6; 
	double result, error;

	gsl_integration_qag(&f_for_integration, 0, z, acc, eps, max_iterations, key, workspace, &result, &error);
	
	gsl_integration_workspace_free(workspace);

	return result;
}
