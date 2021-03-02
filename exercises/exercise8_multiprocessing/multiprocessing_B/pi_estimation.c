#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "throw_points.h"

int main()
{
	int total_number = 1e6;

	struct parameters parameters_thread_1 = {.number = total_number/3, .number_in_circle = 0, .seed = 3};
	struct parameters parameters_thread_2 = {.number = total_number/3, .number_in_circle = 0, .seed = 7};
	struct parameters parameters_thread_3 = {.number = total_number/3, .number_in_circle = 0, .seed = 13};

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			throw_points((void *) &parameters_thread_1);
		}
		#pragma omp section
		{
			throw_points((void *) &parameters_thread_2);
		}
		#pragma omp section
		{
			throw_points((void *) &parameters_thread_3);
		}
	}

	int total_number_in_circle = parameters_thread_1.number_in_circle 
		+ parameters_thread_2.number_in_circle 
		+ parameters_thread_1.number_in_circle;
	
	double pi = 4*(double) total_number_in_circle/total_number;

	printf("The estimate of pi is %g with error %g \n", pi, fabs(pi - M_PI));	

	return 0;
}
