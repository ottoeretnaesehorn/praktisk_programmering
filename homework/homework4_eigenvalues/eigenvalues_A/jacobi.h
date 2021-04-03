#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

int is_matrix_symmetric (gsl_matrix * A)
{
	gsl_matrix AT = gsl_matrix_transpose_memcpy (AT, A);

	if (gsl_matrix_equal (A, AT) == 1)
	{
		return 1; 
	}
	else 
	{
		return 0;
	}
}

void apply_jacobi_right (gsl_matrix * A, int p, int q, double theta)
{
	double Aip;
	double Aiq;

	for (int i = 0; i < A->size1; i++)
	{
		Aip = cos (theta)*gsl_matrix_get (A, i, p) - sin (theta)*gsl_matrix_get (A, i, q);
		Aiq = sin (theta)*gsl_matrix_get (A, i, p) + cos (theta)*gsl_matrix_get (A, i, q);
	
		gsl_matrix_set (A, i, p, Aip);
		gsl_matrix_set (A, i, q, Aiq);
	}
}

void apply_jacobi_left (gsl_matrix * A, int p, int q, double theta)
{
	double Api; 
	double Aqi; 

	for (int i = 0; i < A->size2; i++)
	{
		Api = cos (theta)*gsl_matrix_get (A, p, i) + sin (theta)*gsl_matrix_get (A, q, i);
		Aqi = - sin (theta)*gsl_matrix_get (A, p, i) + cos (theta)*gsl_matrix_get (A, q, i);
		
		gsl_matrix_set (A, p, i, Api); 
		gsl_matrix_set (A, q, i, Aqi);
	}
}

void jacobi_diagonalisation (gsl_matrix * A, gsl_matrix * V)
{
	if (is_matrix_symmetric (A) == 0)
	{
		fprintf (stderr, "Cannot diagonalise non-symmetric matrix\n");
		break;
	}

	int n = A->size1; 

	double App; 
	double Apq;
	double Aqq;

	double theta;

	double new_App;
	double new_Aqq;

	int change; 

	do 
	{
		change = 0; 

		for (int p = 0; p < n - 1; p++)
		{
			for (int q = p + 1; q < n; q++)
			{
				App = gsl_matrix_get (A, p, p); 
				Apq = gsl_matrix_get (A, p, q);
			       	Aqq = gsl_matrix_get (A, q, q);

				theta = 0.5*atan2(2*Apq, Aqq - App);
				
				new_App = cos (theta)*cos (theta)*App 
					- 2*cos (theta)*sin (theta)*Apq
					+ sin (theta)*sin (theta)*Aqq;
				new_Aqq = sin (theta)*sin (theta)*App 
					+ 2*cos (theta)*sin (theta)*Apq
					+ cos (theta)*cos (theta)*Aqq;

				if (new_App != App || new_Aqq != Aqq)
				{
					change = 1; 
					
					apply_jacobi_right (A, p, q, theta); 
					apply_jacobi_left (A, p, q, theta);
					
					apply_jacobi_right (V, p, q, theta);
				}	
			}
		}	
	}
	while (change != 0);

}
