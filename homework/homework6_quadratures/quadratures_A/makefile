CC = gcc
CFLAGS = -O -Wall -std=gnu11
LDLIBS = -lm
HEADERS	= integrate.h 

default : test
	@./$<

test : test.o
	@$(CC) $< -o $@ $(LDLIBS) $(HEADERS)

test.o : test.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<



.PHONEY : clean 

clean : 
	@$(RM) test *.o
