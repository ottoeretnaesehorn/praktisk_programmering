#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	FILE *fptr = fopen("./input.txt","r");
	int input;
	double x;
	
	while(1)
	{
		input = fscanf(fptr, "%lf", &x);

		if (input == 1)
		{
			printf("x = %g \t sin(x) = %g \n", x, sin(x));
		}
		else 
		{
			break;
		}
	};
	
	fclose(fptr);

	return 0;
}
