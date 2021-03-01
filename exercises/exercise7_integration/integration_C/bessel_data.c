#include <stdio.h>
#include <math.h>
#include "bessel.h"

int main()
{
	double min = -5.1; 
	double max = 5.1; 
	double inc = 1.0/8; 

	for (double x = min; x <= max; x += inc)
	{
		printf("%10g %10g %10g %10g \n", x, bessel(x, 0), bessel(x, 1), bessel(x, 2));
	}

	return 0;
}
