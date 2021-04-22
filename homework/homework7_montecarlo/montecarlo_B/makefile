CC = gcc
CFLAGS = -O -Wall -std=gnu11
LDLIBS = -lm
HEADERS = monte_carlo.h

default : test 
	@./$<

test : test.o
	@$(CC) $< -o $@ $(LDLIBS) $(HEADERS)

test.o : test.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<



.PHONEY : clean 

clean : 
	@$(RM) test *.o
