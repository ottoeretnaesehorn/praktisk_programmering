CC = gcc
CFLAGS = -Wall -O -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
HEADERS = jacobi.h printing.h
OUTPUT = out.txt

default : out.txt
	@cat $<
	
$(OUTPUT) : particle_in_a_box  
	@./$< > $@

particle_in_a_box : particle_in_a_box.o
	@$(CC) $< -o $@ $(LDLIBS) $(HEADERS)

particle_in_a_box.o : particle_in_a_box.c
	@$(CC) $(CFLAGS) $< -c



.PHONEY	: clean 

clean : 
	@$(RM) *.o particle_in_a_box 
