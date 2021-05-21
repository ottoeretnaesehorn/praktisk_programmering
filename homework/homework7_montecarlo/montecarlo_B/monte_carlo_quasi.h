complex monte_carlo_quasi (
		int dim, 
		double f (double * x), 
		double * a, 
		double * b, 
		int N
		);

void halton1 (
		int n, 
		int d, 
		double * a, 
		double * b, 
		double * x
	     );
void halton2 (
		int n, 
		int d, 
		double * a, 
		double * b, 
		double * x
	     );

double corput (
		int n,
		int base
	     );
