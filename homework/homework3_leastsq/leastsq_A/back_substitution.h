#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

void back_substitution (gsl_matrix * U, gsl_vector * c)
{
	for (int i = c->size - 1; i >= 0; i--)
	{
		double sum = gsl_vector_get (c, i);
		
		for (int j = i + 1; j < c->size; j++)
		{
			sum -= gsl_matrix_get (U, i, j)*gsl_vector_get (c, j);
		}

		gsl_vector_set (c, i, sum/gsl_matrix_get (U, i, i));
	}
}
