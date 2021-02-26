CC = gcc
CFLAGS = -O -std=gnu11 -Wall $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)



default : lngamma.svg 


lngamma.svg : lngamma.gpi lngamma_data.txt
	@gnuplot $<

lngamma_data.txt : lngamma_data_generator
	@./$< > $@

lngamma_data_generator : lngamma_data_generator.o
	@$(CC) $< -o $@ $(LDLIBS)

lngamma_data_generator.o : lngamma_data_generator.c
	@$(CC) $(CFLAGS) $< -c 



.PHONEY : clean 

clean : 
	@$(RM) *.txt *.svg lngamma_data_generator *.o 
