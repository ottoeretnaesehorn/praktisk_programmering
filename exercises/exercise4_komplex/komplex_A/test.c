#include <stdio.h>
#include "komplex_with_functions.h"

int main()
{
	komplex z1 = {1, 1};
	komplex z2 = komplex_new(2, 2);

	printf("Testing basic komplex functions:\n");

	komplex_print("z1 = ", z1);
	komplex_print("z2 = ", z2);

	printf("\nTesting algebraic komplex functions:\n");
	printf("|z1|^2 = %f\n", komplex_norm(z1));
	komplex_print("z1 + z2 = ", komplex_add(z1, z2));
	komplex_print("z1 - z2 = ", komplex_subtract(z1, z2));
	komplex_print("z1*z2 = ", komplex_multiply(z1, z2));
	komplex_print("z1/z2 = ", komplex_divide(z1, z2));
	
	return 0;
}
