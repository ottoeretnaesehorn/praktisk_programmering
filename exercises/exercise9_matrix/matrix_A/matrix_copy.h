#include <gsl/gsl_matrix.h>

gsl_matrix * matrix_copy (gsl_matrix * A)
{
	int rows = A -> size1;
	int columns = A -> size2;

	gsl_matrix * new_matrix = gsl_matrix_alloc(rows, columns);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			gsl_matrix_set (new_matrix, i, j, gsl_matrix_get(A, i, j));
		};
	};

	return new_matrix;
}
