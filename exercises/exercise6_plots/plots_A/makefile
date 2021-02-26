CC = gcc
CFLAGS = -O -std=gnu11 -Wall $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)



default : erf.svg gamma.svg 



gamma.svg : gamma.gpi gamma_data.txt
	@gnuplot $<

gamma_data.txt : gamma_data_generator
	@./$< > $@

gamma_data_generator : gamma_data_generator.o
	@$(CC) $< -o $@ $(LDLIBS)

gamma_data_generator.o : gamma_data_generator.c
	@$(CC) $(CFLAGS) $< -c 



erf.svg : erf.gpi erf_data.txt
	@gnuplot $<

erf_data.txt : erf_data_generator
	@./$< > $@

erf_data_generator : erf_data_generator.o
	@$(CC) $< -o $@ $(LDLIBS)

erf_data_generator.o : erf_data_generator.c
	@$(CC) $(CFLAGS) $< -c 



.PHONEY : clean 

clean : 
	@$(RM) *.txt *.svg gamma_data_generator erf_data_generator *.o 
