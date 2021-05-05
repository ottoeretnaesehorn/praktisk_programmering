double adapt (
		double f (double t), 
		double min, 
		double max, 
		double acc, 
		double eps, 
		double f2,
	       	double f3,	
		int recursions
	     );
double integrate(
		double f (double t), 
		double min, 
		double max, 
		double acc, 
		double eps
		);

double clenshaw_curtis(
		double f (double t), 
		double min, 
		double max, 
		double acc, 
		double eps
		); 
