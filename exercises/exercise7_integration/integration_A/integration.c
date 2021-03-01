#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

double f (double x, void * params)
{
	return log(x)/sqrt(x);
}

int main()
{
	gsl_function f_for_integration; 
	f_for_integration.function = &f;
	f_for_integration.params = 0;

	int max_iterations = 999; 
	
	gsl_integration_workspace* workspace = gsl_integration_workspace_alloc(max_iterations);
	double acc = 1e-6, eps = 1e-6; 
	double result, error;

	double min = 0, max = 1;

	gsl_integration_qags(&f_for_integration, min, max, acc, eps, max_iterations, workspace, &result, &error);
	printf("The integral from 0 to 1 of log(x)/sqrt(x) evaluates to %g with error %g \n", result, error);
	printf("The analytical value of the integral is -4\n");

	gsl_integration_workspace_free(workspace);	

	return 0;
}
