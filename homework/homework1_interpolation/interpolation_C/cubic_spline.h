typedef struct 
{
	int n; 
	
	double * x; 
	double * y; 
	
	double * b; 
	double * c;
	double * d;	
} cubic_spline;

cubic_spline * cubic_spline_alloc (int n, double * x, double * y); 

double cubic_spline_eval (cubic_spline * spline, double z); 
double cubic_spline_integ (cubic_spline * spline, double z); 
double cubic_spline_deriv (cubic_spline * spline, double z); 

void cubic_spline_free (cubic_spline * spline);
