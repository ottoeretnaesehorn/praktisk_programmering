CC = gcc
CFLAGS = -Wall -O -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
HEADERS = gram_schmidt.h printing.h

default : out.txt
	@cat $<
	
out.txt : test
	@./$< > $@

test : test.o
	@$(CC) $< -o $@ $(LDLIBS) $(HEADERS)

test.o : test.c
	@$(CC) $(CFLAGS) $< -c



.PHONEY : clean 

clean : 
	@$(RM) *.txt test *.o 
