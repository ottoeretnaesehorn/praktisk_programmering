#include <stdio.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include "printing.h"

void print_matrix (char str[], gsl_matrix * A)
{
        printf ("%s(", str);

        for (int i = 0; i < A->size1; i++)
        {
                for (int j = 0; j < A->size2; j++)
                {
                        if (j == A->size2 - 1)
                        {
                                if (i == A->size1 - 1)
                                {
                                        printf ("%f) \n", gsl_matrix_get (A, i, j));
                                }
                                else
                                {
                                        printf ("%f; \n", gsl_matrix_get (A, i, j));
                                }
                        }
                        else
                        {
                                printf ("%f, ", gsl_matrix_get (A, i, j));
                        }
                }
        }
}

void print_vector (char str[], gsl_vector * x)
{
	printf ("%s(", str);

	for (int i = 0; i < x->size; i++)
	{
		if (i == x->size - 1)
		{
			printf ("%f) \n", gsl_vector_get (x, i));
		}
		else 
		{
			printf ("%f, ", gsl_vector_get (x, i));
		}
	}
}
