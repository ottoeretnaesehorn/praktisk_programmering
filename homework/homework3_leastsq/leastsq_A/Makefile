CC = gcc
CFLAGS = -Wall -O -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
OBJFILES = main.o least_squares.o gram_schmidt.o
OUTPUT = data.txt plot.txt out.txt
 


default : out.txt plot.svg
	@cat $<

plot.svg : plot.gpi data.txt plot.txt
	@gnuplot $<
	
$(OUTPUT) : main
	@./$< > $@ 

main : $(OBJFILES)
	@$(CC) -o $@ $^ $(LDLIBS)

main.o : main.c least_squares.h gram_schmidt.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

least_squares.o : least_squares.c least_squares.h gram_schmidt.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

gram_schmidt.o : gram_schmidt.c gram_schmidt.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<



.PHONEY : clean 

clean : 
	@$(RM) *.svg *.txt main *.o
