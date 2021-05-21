CC = gcc
CFLAGS = -O -Wall -std=gnu11
LDLIBS = -lm
OBJFILES = main.o monte_carlo_strata.o



default : out.txt
	@cat $<
	
out.txt : main 
	@./$< > $@

main : $(OBJFILES)
	@$(CC) -o $@ $^ $(LDLIBS)

main.o : main.c monte_carlo_strata.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

monte_carlo_strata.o : monte_carlo_strata.c monte_carlo_strata.h 
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<



.PHONEY : clean 

clean : 
	@$(RM) *.txt main *.o
