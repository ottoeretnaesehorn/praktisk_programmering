CC = gcc
CFLAGS = -Wall -O -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
HEADERS = jacobi.h

default : test 
	@./$<

test : test.o
	@$(CC) $< -o $@ $(LDLIBS) $(HEADERS)

test.o : test.c
	@$(CC) $(CFLAGS) $< -c



.PHONEY	: clean 

clean : 
	@$(RM) *.o test 
