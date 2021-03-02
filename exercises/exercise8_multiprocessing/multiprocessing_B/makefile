CC = gcc
CFLAGS = -O -Wall -std=gnu11 -fopenmp
LDLIBS = -lm -lgomp



default : out.txt
	@cat $<

out.txt : pi_estimation
	@./$< > $@

pi_estimation : pi_estimation.o
	@$(CC) $< -o $@ $(LDLIBS)

pi_estimation.o : pi_estimation.c throw_points.h
	@$(CC) $(CFLAGS) $< -c 



.PHONEY : clean 

clean : 
	@$(RM) *.txt pi_estimation *.o
