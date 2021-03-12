#include <stdio.h>
#include <math.h>
#include "exponential.h"

int main()
{
	double min = -5.01; 
	double max = 5.01; 
	double inc = 1./8; 

	for (double x = min; x <= max; x += inc)
	{
		printf("%10g %10g %10g\n", x, exp(x), exponential(x));
	}

	return 0; 
}
