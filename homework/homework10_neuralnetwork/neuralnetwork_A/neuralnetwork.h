typedef struct 
{
	int n; 
	double (* f) (double t); 
	gsl_vector * parameters; 
} NN;

NN * NN_alloc (int n, double (* f) (double t)); 
void NN_free (NN * network);
void NN_train (NN * network, gsl_vector * x, gsl_vector * y); 

double NN_response (NN * network, double x); 
