CC = gcc
CFLAGS = -O -Wall -Werror -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
HEADERS = cubic_spline.h binary_search.h value_check.h

default : spline.svg spline_integ.svg spline_deriv.svg

spline_deriv.svg : spline_deriv.gpi spline_data.txt
	@gnuplot $<

spline_integ.svg : spline_integ.gpi spline_data.txt
	@gnuplot $<

spline.svg : spline.gpi spline_data.txt points.txt
	@gnuplot $<

spline_data.txt points.txt : test 
	@./$<

test : test.o 
	@$(CC) $< -o $@ $(LDLIBS) $(HEADERS)

test.o : test.c
	@$(CC) $(CFLAGS) $< -c



.PHONEY : clean 

clean : 
	@$(RM) *.svg *.txt test *.o 
