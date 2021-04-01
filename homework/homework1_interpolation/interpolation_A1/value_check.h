#include <assert.h>

void value_check (int n, double x[], double z)
{
	assert (z >= x[0] && z <= x[n - 1]);
}
