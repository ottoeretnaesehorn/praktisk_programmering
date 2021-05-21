typedef struct 
{
	int n; 
	double (* function) (double t); 
	double (* derivative) (double t); 
	double (* integral) (double t); 
	gsl_vector * parameters; 
} NN;

NN * NN_alloc (int n, 
		double (* function) (double t),
		double (* derivative) (double t),
		double (* integral) (double t)); 
void NN_free (NN * network);
void NN_train (NN * network, gsl_vector * x, gsl_vector * y); 

double NN_response (NN * network, double x); 
double NN_derivative (NN * network, double x); 
double NN_integral (NN * network, double x); 

