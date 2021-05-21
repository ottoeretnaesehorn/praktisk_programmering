double monte_carlo_strata (
		int dim, 
		double f (double * x), 
		double * a, 
		double * b, 
		double acc,
		double eps, 
		double n_reuse, 
		double mean_reuse
		);
