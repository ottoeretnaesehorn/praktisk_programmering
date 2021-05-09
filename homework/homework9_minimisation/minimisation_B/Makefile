CC = gcc
CFLAGS = -O -Wall -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
OBJFILES = main.o quasi_newton.o printing.o



default : out.txt plot.svg
	@cat $<	
	
plot.svg : plot.gpi points.txt
	@gnuplot $<

data.txt points.txt out.txt log.txt : main
	@./$< > out.txt 2> log.txt

main : $(OBJFILES)
	@$(CC) -o $@ $^ $(LDLIBS)

main.o : main.c quasi_newton.h printing.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

quasi_newton.o : quasi_newton.c quasi_newton.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

printing.o : printing.c printing.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<



.PHONEY : clean 

clean : 
	@$(RM) *.txt main *.o
