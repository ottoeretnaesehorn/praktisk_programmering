CC = gcc
CFLAGS = -O -std=gnu11 -Wall $(shell gsl-config --cflags) 
LDLIBS = -lm $(shell gsl-config --libs)
HEADERS = runge_kutta.h matrix_add_row.h

default : plot.svg
	
plot.svg : plot.gpi out.txt
	@gnuplot $<
	
out.txt : test
	@./$< > $@

test : test.o
	@$(CC) $< -o $@ $(LDLIBS) $(HEADERS)

test.o : test.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $< 



.PHONEY : clean 

clean : 
	@$(RM) test *.o *.txt *.svg 
