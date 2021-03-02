#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "throw_points.h"

int main()
{
	int total_number = 1e6;

	struct parameters parameters_thread_1 = {.number = total_number/3, .number_in_circle = 0, .seed = 3};
	struct parameters parameters_thread_2 = {.number = total_number/3, .number_in_circle = 0, .seed = 7};
	struct parameters parameters_thread_3 = {.number = total_number/3, .number_in_circle = 0, .seed = 13};

	pthread_t thread_1, thread_2, thread_3;

	pthread_create(&thread_1, NULL, throw_points, (void *) &parameters_thread_1);
	pthread_create(&thread_2, NULL, throw_points, (void *) &parameters_thread_2);
	pthread_create(&thread_3, NULL, throw_points, (void *) &parameters_thread_3);

	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	pthread_join(thread_3, NULL);

	int total_number_in_circle = parameters_thread_1.number_in_circle 
		+ parameters_thread_2.number_in_circle 
		+ parameters_thread_1.number_in_circle;
	
	double pi = 4*(double) total_number_in_circle/total_number;

	printf("The estimate of pi is %g with error %g \n", pi, fabs(pi - M_PI));	

	return 0;
}
