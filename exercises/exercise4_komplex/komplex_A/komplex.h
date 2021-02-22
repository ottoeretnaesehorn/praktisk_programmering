#ifndef KOMPLEX
#define KOMPLEX

typedef struct 
{
	double re, im; 
} komplex;

void komplex_set (komplex* z, double x, double y);
komplex komplex_new (double x, double y);

void komplex_print (char* s, komplex z); 

double komplex_norm (komplex z);
komplex komplex_add (komplex z1, komplex z2);
komplex komplex_subtract (komplex z1, komplex z2); 
komplex komplex_multiply (komplex z1, komplex z2);
komplex komplex_divide (komplex z1, komplex z2);

#endif
