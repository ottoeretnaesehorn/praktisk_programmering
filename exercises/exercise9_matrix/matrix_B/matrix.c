#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_eigen.h>

gsl_matrix * define_matrix (int n)
{
	gsl_matrix * H = gsl_matrix_alloc(n, n); 

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			gsl_matrix_set(H, i, j, 1.0/(i + j + 1));
		}
	}

	return H; 
}

void eigen_print (gsl_vector * eigenvalues, gsl_matrix * eigenvectors, int n)
{
	printf("%f, (%f, %f, %f, %f)\n", gsl_vector_get (eigenvalues, n), gsl_matrix_get (eigenvectors, n, 0), gsl_matrix_get (eigenvectors, n, 1), gsl_matrix_get (eigenvectors, n, 2), gsl_matrix_get (eigenvectors, n, 3));
}

int main() 
{
	int n = 4; 

	gsl_matrix * H = define_matrix (n);
	gsl_vector * eigenvalues = gsl_vector_alloc (n); 
	gsl_matrix * eigenvectors = gsl_matrix_alloc (n, n);

	gsl_eigen_symmv_workspace * workspace = gsl_eigen_symmv_alloc (n); 
	gsl_eigen_symmv (H, eigenvalues, eigenvectors, workspace);
	gsl_eigen_symmv_free (workspace);
	
	printf("Eigenvalues and corresponding eigenvectors:\n");
	eigen_print(eigenvalues, eigenvectors, 0);
	eigen_print(eigenvalues, eigenvectors, 1);
	eigen_print(eigenvalues, eigenvectors, 2);
	eigen_print(eigenvalues, eigenvectors, 3);
	
	gsl_matrix_free (H);
	gsl_vector_free (eigenvalues);
	gsl_matrix_free (eigenvectors);
	
	return 0; 
}
