#include <stdio.h>
#include <limits.h>



void calculate_max_int_using_while()
{
	int i = 1; 
	
	while (i + 1 > i) 
	{
		i++;
	}

	printf("int_max = %d (Using while loop)\n", i);
}

void calculate_max_int_using_for()
{
	int i; 
	for (i = 1; i + 1 > 1; i++);

	printf("int_max = %d (Using for loop)\n", i);
}

void calculate_max_int_using_do_while()
{
	int i = 1; 

	do 
	{
		i++;
	}
	while (i + 1 > i); 

	printf("int_max = %d (Using do/while loop)\n", i);
}


int main()
{
	printf("Investigating maximum integer:\n");
	calculate_max_int_using_while();
	calculate_max_int_using_for();
	calculate_max_int_using_do_while();
	printf("int_max = %d (From limits.h)\n", INT_MAX);

	return 0;
}
