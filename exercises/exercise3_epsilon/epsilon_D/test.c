#include <stdio.h>
#include "name_of_digit.h"

int main()
{
	int number;
	int input;	

	printf("Enter digit: ");
	input = scanf("%d", &number);
	
	if (input == 1)
	{
		printf("\nYou entered the digit ");
		name_of_digit(number);
	}
	else 
	{
		printf("You must enter a digit\n");
	}

	return 0;
}

