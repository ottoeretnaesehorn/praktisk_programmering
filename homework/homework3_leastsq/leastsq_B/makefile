CC = gcc
CFLAGS = -Wall -O -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)

default : fit
	@./$<

fit : fit.o
	@$(CC) $< -o $@ $(LDLIBS)

fit.o : fit.c
	@$(CC) $(CFLAGS) $< -c



.PHONEY : clean 

clean : 
	@$(RM) fit *.o
