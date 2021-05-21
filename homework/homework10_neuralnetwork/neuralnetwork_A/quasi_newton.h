int quasi_newton (
		double f (gsl_vector * x), 
	       	gsl_vector * x, 
		double eps	
		);
void numeric_gradient (
		double f (gsl_vector * x),
		gsl_vector * x, 
		gsl_vector * grad
		); 
