CC = gcc
CFLAGS = -Wall -O -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
OBJFILES = main.o least_squares.o gram_schmidt.o



default : out.txt
	@cat $<
	
out.txt : main
	@./$< > $@

main : $(OBJFILES)
	@$(CC) -o $@ $^ $(LDLIBS)

main.o : main.c least_squares.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

least_squares.o : least_squares.c least_squares.h gram_schmidt.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

gram_schmidt.o : gram_schmidt.c gram_schmidt.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<



.PHONEY : clean 

clean : 
	@$(RM) *.txt main *.o
