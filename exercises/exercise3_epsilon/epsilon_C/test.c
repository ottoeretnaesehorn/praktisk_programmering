#include <stdio.h>
#include "equal.h"

int main()
{
	printf("Testing equal.h:\n");

	double tau = 1.0e-6; 
	double epsilon = 1.0e-6;

	if (equal(1, 2, tau, epsilon) == 1)
	{
		printf("1 = 2 (failed)\n");
	}
	else 
	{
		printf("1 != 2 (passed)\n");
	}

	if (equal(1, 1, tau, epsilon) == 0)
	{
		printf("1 != 1 (failed)\n");
	}
	else
	{
		printf("1 = 1 (passed)\n");
	}

	return 0; 
}
