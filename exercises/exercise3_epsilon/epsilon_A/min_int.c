#include <stdio.h>
#include <limits.h>



void calculate_min_int_using_while()
{
	int i = 1; 
	
	while (i - 1 < i) 
	{
		i--;
	}

	printf("int_min = %d (Using while loop)\n", i);
}

void calculate_min_int_using_for()
{
	int i; 
	for (i = 1; i - 1 < i; i--);

	printf("int_min = %d (Using for loop)\n", i);
}

void calculate_min_int_using_do_while()
{
	int i = 1; 

	do 
	{
		i--;
	}
	while (i - 1 < i); 

	printf("int_min = %d (Using do/while loop)\n", i);
}


int main()
{
	printf("Investigating minimum integer:\n");
	calculate_min_int_using_while();
	calculate_min_int_using_for();
	calculate_min_int_using_do_while();
	printf("int_min = %d (From limits.h)\n", INT_MIN);

	return 0;
}
