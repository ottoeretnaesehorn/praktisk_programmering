#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argument_count, char** arguments)
{
	if (argument_count < 2)
	{
		printf("No arguments were given\n");
	}
	else 
	{
		for (int i = 1; i < argument_count; i++)
		{
			double x = atof(arguments[i]);
			
			printf("x = %g \t sin(x) = %g \n", x, sin(x));
		}
	}

	return 0;
}
