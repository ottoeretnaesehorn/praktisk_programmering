CC = gcc
CFLAGS = -O -Wall -std=gnu11 -fopenmp
LDLIBS = -lm -lgomp



default : convergence.svg

convergence.svg : convergence.gpi out.txt
	@gnuplot $<

out.txt : estimation_convergence
	@./$< > $@

estimation_convergence : estimation_convergence.o
	@$(CC) $< -o $@ $(LDLIBS)

estimation_convergence.o : estimation_convergence.c pi_estimation.h throw_points.h
	@$(CC) $(CFLAGS) $< -c 



.PHONEY : clean 

clean : 
	@$(RM) *.svg *.txt estimation_convergence *.o
