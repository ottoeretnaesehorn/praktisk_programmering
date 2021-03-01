CC = gcc
CFLAGS = -O -std=gnu11 -Wall $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)



default : error_function.svg

error_function.svg : error_function.gpi data.txt
	@gnuplot $<

data.txt : error_function_data
	@./$< > $@

error_function_data : error_function_data.o 
	@$(CC) $< -o $@ $(LDLIBS)

error_function_data.o : error_function_data.c error_function.h
	@$(CC) $(CFLAGS) $< -c



.PHONEY : clean 

clean : 
	@$(RM) *.svg *.txt error_function_data *.o
