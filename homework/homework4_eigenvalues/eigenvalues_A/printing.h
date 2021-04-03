#include <stdio.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

void print_matrix (FILE * out, char str[], gsl_matrix * A)
{
        fprintf (out, "%s(", str);

        for (int i = 0; i < A->size1; i++)
        {
                for (int j = 0; j < A->size2; j++)
                {
                        if (j == A->size2 - 1)
                        {
                                if (i == A->size1 - 1)
                                {
                                        fprintf (out, "%f) \n", gsl_matrix_get (A, i, j));
                                }
                                else
                                {
                                        fprintf (out, "%f; \n", gsl_matrix_get (A, i, j));
                                }
                        }
                        else
                        {
                                fprintf (out, "%f, ", gsl_matrix_get (A, i, j));
                        }
                }
        }
}

void print_vector (FILE * out, char str[], gsl_vector * x)
{
	fprintf (out, "%s(", str);

	for (int i = 0; i < x->size; i++)
	{
		if (i == x->size - 1)
		{
			fprintf (out, "%f) \n", gsl_vector_get (x, i));
		}
		else 
		{
			fprintf (out, "%f, ", gsl_vector_get (x, i));
		}
	}
}
