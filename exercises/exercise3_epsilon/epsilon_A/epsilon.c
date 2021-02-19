#include <stdio.h>
#include <float.h>



void calculate_float_epsilon()
{
	float x = 1; 

	while (1 + x != 1) 
	{
		x /= 2; 
	};
	
	x *= 2;

	printf("epsilon_float = %g (Calculated)\n", x);	
}

void calculate_double_epsilon()
{
	double x = 1; 

	while (1 + x != 1) 
	{
		x /= 2; 
	};
	
	x *= 2;

	printf("epsilon_double = %g (Calculated)\n", x);	
}

void calculate_long_double_epsilon()
{
	long double x = 1; 

	while (1 + x != 1) 
	{
		x /= 2; 
	};
	
	x *= 2;

	printf("epsilon_long_double = %Lg (Calculated)\n", x);	
}



int main()
{
	printf("Investigating the machine epsilon:\n");
	calculate_float_epsilon();
	printf("epsilon_float = %g (From float.h)\n", FLT_EPSILON);
	calculate_double_epsilon();
	printf("epsilon_double = %g (From float.h)\n", DBL_EPSILON);
	calculate_long_double_epsilon();
	printf("epsilon_long_double = %Lg (From float.h)\n", LDBL_EPSILON);

	return 0;
}
