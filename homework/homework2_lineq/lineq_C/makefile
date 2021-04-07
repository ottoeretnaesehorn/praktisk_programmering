CC = gcc
CFLAGS = -Wall -O -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
HEADERS = gram_schmidt.h

default : decomposition_time.svg

decomposition_time.svg : decomposition_time.gpi out.txt
	@gnuplot $<

out.txt : decomposition_time
	@./$< > $@

decomposition_time : decomposition_time.o
	@$(CC) $< -o $@ $(LDLIBS) $(HEADERS)

decomposition_time.o : decomposition_time.c
	@$(CC) $(CFLAGS) $< -c



.PHONEY : clean 

clean : 
	@$(RM) *.svg *.txt decomposition_time *.o 
