#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_matrix.h>

void matrix_add_row (gsl_matrix * A)
{
	if (!A)
	{
		fprintf (stderr, "Matrix must be initialised to add row");
		exit (1); 
	}

	size_t n = A->tda; 

	A->block->data = (double *) realloc (A->block->data, sizeof (double)*(A->block->size + n)); 

	if (!A->block->data)
	{
		fprintf (stderr, "Couldn't reallocate memory for matrix"); 
		exit (1); 
	}

	A->block->size += n; 
	A->size1++; 
	A->data = A->block->data; 
}
