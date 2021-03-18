CC = gcc
CFLAGS = -O -Wall -Werror -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)



default : linear_spline_integrated.svg linear_spline.svg

linear_spline_integrated.svg : linear_spline_integrated.gpi spline_integrated.txt
	@gnuplot $<

linear_spline.svg : linear_spline.gpi spline.txt points.txt
	@gnuplot $<

spline_integrated.txt spline.txt points.txt : test 
	@./$< > $@

test : test.o 
	@$(CC) $< -o $@ $(LDLIBS) quadratic_spline.h binary_search.h 

test.o : test.c
	@$(CC) $(CFLAGS) $< -c



.PHONEY : clean 

clean : 
	@$(RM) *.svg *.txt test *.o 
