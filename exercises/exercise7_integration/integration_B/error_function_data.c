#include <stdio.h>
#include <math.h>
#include "error_function.h"

int main()
{
	double min = -5.1; 
	double max = 5.1; 
	double inc = 1.0/8; 

	for (double x = min; x <= max; x += inc)
	{
		printf("%10g %10g \n", x, error_function(x));
	}

	return 0;
}
