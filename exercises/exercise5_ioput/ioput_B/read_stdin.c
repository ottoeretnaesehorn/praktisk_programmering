#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	double x;
	int input;

	for (int i = 0; i <= 15; i++)
	{
		input = scanf("%lf", &x);

		if (input == 1)
		{
			printf("x = %g \t sin(x) = %g \n", x, sin(x));
		}
		else 
		{
			break;
		};
		
		if (i == 15)
		{
			printf("This program takes no more than 15 arguments\n");
		};
	};

	return 0;
}
