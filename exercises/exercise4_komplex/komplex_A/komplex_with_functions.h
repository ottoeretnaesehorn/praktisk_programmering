#include <stdio.h>
#include <math.h>
#include "komplex.h"

void komplex_set (komplex* z, double x, double y)
{
	(*z).re = x;
	(*z).im = y;
}

komplex komplex_new (double x, double y)
{
	komplex z = {x, y};

	return z;
}



void komplex_print (char *s, komplex z)
{
	printf("%s(%g, %g)\n", s, z.re, z.im);
}



double komplex_norm (komplex z)
{
	return sqrt(pow(z.re, 2) + pow(z.im, 2));
}

komplex komplex_add (komplex z1, komplex z2)
{
	return komplex_new(z1.re + z2.re, z1.im + z2.im);
}

komplex komplex_subtract (komplex z1, komplex z2)
{
	return komplex_new(z1.re - z2.re, z1.im - z2.im);
}

komplex komplex_multiply (komplex z1, komplex z2)
{
	return komplex_new(z1.re*z2.re - z1.im*z2.im, z1.re*z2.im + z1.im*z2.re);
}

komplex komplex_divide (komplex z1, komplex z2)
{
	double z2_norm_square = pow(komplex_norm(z2), 2);

	return komplex_new((z1.re*z2.re + z1.im*z2.im)/z2_norm_square, (z1.im*z2.re - z1.re*z2.im)/z2_norm_square);
}

