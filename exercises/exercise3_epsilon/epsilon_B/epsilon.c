#include <stdio.h>
#include <limits.h>



void float_sums()
{
	int max = INT_MAX/2; 

	float sum_up_float; 
	float sum_down_float; 

	for (int i = 1; i <= max; i++)
	{
		sum_up_float += 1.0f/i;
		sum_down_float += 1.0f/(max + 1 - i);
	};

	printf("The sum from above = %g (Using floats)\n", sum_down_float);
	printf("The sum from below = %g (using floats)\n", sum_up_float);
}

void double_sums()
{
	int max = INT_MAX/2; 

	double sum_up_double; 
	double sum_down_double; 

	for (int i = 1; i <= max; i++)
	{
		sum_up_double += 1.0/i;
		sum_down_double += 1.0/(max + 1 - i);
	};

	printf("The sum from above = %g (Using doubles)\n", sum_down_double);
	printf("The sum from below = %g (Using doubles)\n", sum_up_double);
}



int main()
{
	float_sums();
	double_sums();
	printf("\nThe series doesn't converge mathematically\n");
	printf("The result is due to finite precision\n");

	return 0;
}
