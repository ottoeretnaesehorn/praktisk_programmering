#include <stdlib.h>

struct parameters 
{
	int number;
	int number_in_circle; 
	unsigned int seed; 
};

void * throw_points(void * arguments)
{
	struct parameters * given = (struct parameters *) arguments;
	given -> number_in_circle = 0;

	for (int i = 0; i < given -> number; i++)
	{
		double x = (double) rand_r(&(given -> seed))/RAND_MAX;
		double y = (double) rand_r(&(given -> seed))/RAND_MAX;

		if (x*x + y*y < 1)
		{
			given -> number_in_circle++;
		}

	}

	return NULL;
}
