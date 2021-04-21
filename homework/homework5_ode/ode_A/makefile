CC = gcc
CFLAGS = -O -Wall 
LDLIBS = -lm
TXTFILES = susceptible.txt infectious.txt removed.txt

default : plot.svg
	
plot.svg : plot.gpi $(TXTFILES)
	@gnuplot $<
	
$(TXTFILES) : sir_model
	@./$< > $@

sir_model : sir_model.o
	@$(CC) $< -o $@ $(LDLIBS) runge_kutta.h

sir_model.o : sir_model.c
	@$(CC) $< -c 



.PHONEY : clean 

clean : 
	@$(RM) sir_model *.o *.txt *.svg 
