CC = gcc
CFLAGS = -O -Wall -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
OBJFILES = main.o newton.o printing.o



default : out.txt
	@cat $<

out.txt : main
	@./$< > $@

main : $(OBJFILES)
	@$(CC) -o $@ $^ $(LDLIBS)

main.o : main.c newton.h printing.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

newton.o : newton.c newton.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

printing.o : printing.c printing.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<



.PHONEY : clean 

clean : 
	@$(RM) *.txt main *.o 
