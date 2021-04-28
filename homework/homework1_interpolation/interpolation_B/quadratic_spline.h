typedef struct 
{
	int n; 
	
	double * x; 
	double * y; 
	
	double * b; 
	double * c; 
} 
quadratic_spline;

quadratic_spline * quadratic_spline_alloc (int n, double x[], double y[]);

double quadratic_spline_eval (quadratic_spline * spline, double z);
double quadratic_spline_integ (quadratic_spline * spline, double z0, double z);
double quadratic_spline_deriv (quadratic_spline * spline, double z);

void quadratic_spline_free (quadratic_spline * spline);
