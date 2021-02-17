#include <stdio.h>



int main()
{
	float float_fraction = 1.f/9;
	double double_fraction = 1./9;
	long double long_double_fraction = 1.L/9;

	printf("Value of 1/9 using different types:\n");
	printf("1/9 = %.25g (float)\n", float_fraction);
	printf("1/9 = %.25lg (double)\n", double_fraction);
	printf("1/9 = %.25Lg (long double)\n", long_double_fraction);

	return 0;
}
