CC = gcc
CFLAGS = -Wall -O -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
HEADERS = gram_schmidt.h printing.h
OBJFILES = main.o gram_schmidt.o printing.o



default : out.txt
	@cat $<
	
out.txt : main
	@./$< > $@

main : $(OBJFILES)
	@$(CC) -o $@ $(OBJFILES) $(LDLIBS)

main.o : main.c $(HEADERS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

gram_schmidt.o : gram_schmidt.c gram_schmidt.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

printing.o : printing.c printing.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<



.PHONEY : clean 

clean : 
	@$(RM) *.txt main *.o 
