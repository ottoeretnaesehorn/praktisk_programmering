CC = gcc
CFLAGS = -Wall -O -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
OUTPUT = data.txt plot.txt out.txt

default : out.txt plot.svg
	@cat $<

plot.svg : plot.gpi data.txt plot.txt
	@gnuplot $<
	
$(OUTPUT) : fit
	@./$< > $@ 

fit : fit.o
	@$(CC) $< -o $@ $(LDLIBS)

fit.o : fit.c
	@$(CC) $(CFLAGS) $< -c



.PHONEY : clean 

clean : 
	@$(RM) *.svg *.txt fit *.o
