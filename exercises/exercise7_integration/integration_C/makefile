CC = gcc
CFLAGS = -O -std=gnu11 -Wall $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)



default : bessel.svg

bessel.svg : bessel.gpi data.txt
	@gnuplot $<

data.txt : bessel_data
	@./$< > $@

bessel_data : bessel_data.o 
	@$(CC) $< -o $@ $(LDLIBS)

bessel_data.o : bessel_data.c bessel.h
	@$(CC) $(CFLAGS) $< -c



.PHONEY : clean 

clean : 
	@$(RM) *.svg *.txt bessel_data *.o
