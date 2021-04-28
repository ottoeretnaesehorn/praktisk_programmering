CC = gcc
CFLAGS = -Wall -O -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
OBJFILES = main.o gram_schmidt.o



default : time.svg

time.svg : plot.gpi data.txt
	@gnuplot $<

data.txt : main
	@./$< > $@

main : $(OBJFILES)
	@$(CC) -o $@ $(OBJFILES) $(LDLIBS)

main.o : main.c gram_schmidt.h
	@$(CC) $(CFLAGS) -o $@ -c $<

gram_schmidt.o : gram_schmidt.c gram_schmidt.h
	@$(CC) $(CFLAGS) -o $@ -c $<



.PHONEY : clean 

clean : 
	@$(RM) *.svg *.txt main *.o 
