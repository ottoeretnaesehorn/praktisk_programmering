#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pi_estimation.h"

int main()
{
	int steps = 5e5;

	for (int N = steps; N < 1e7; N += steps)
	{
		printf("%10d %10g \n", N, fabs(pi_estimation(N) - M_PI));
	}

	return 0;
}
