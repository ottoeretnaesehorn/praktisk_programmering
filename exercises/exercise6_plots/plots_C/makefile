CC = gcc
CFLAGS = -O -std=gnu11 -Wall $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)



default : complex_gamma.svg 

complex_gamma.svg : complex_gamma.gpi complex_gamma_data.txt
	@gnuplot $<

complex_gamma_data.txt : complex_gamma_data_generator
	@./$< > $@

complex_gamma_data_generator : complex_gamma_data_generator.o
	@$(CC) $< -o $@ $(LDLIBS)

complex_gamma_data_generator.o : complex_gamma_data_generator.c
	@$(CC) $(CFLAGS) $< -c 



.PHONEY : clean 

clean : 
	@$(RM) *.txt *.svg complex_gamma_data_generator *.o 
