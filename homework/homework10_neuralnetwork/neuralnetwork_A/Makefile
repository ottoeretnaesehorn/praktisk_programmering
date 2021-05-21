CC = gcc
CFLAGS = -O -Wall -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
OBJFILES = main.o neuralnetwork.o quasi_newton.o



default : plot.svg

plot.svg : plot.gpi data.txt points.txt
	@gnuplot $<

data.txt points.txt log.txt : main
	@./$< > data.txt points.txt 2> log.txt 

main : $(OBJFILES)
	@$(CC) -o $@ $^ $(LDLIBS)

main.o : main.c neuralnetwork.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

neuralnetwork.o : neuralnetwork.c neuralnetwork.h quasi_newton.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

quasi_newton.o : quasi_newton.c quasi_newton.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<



.PHONEY : clean 

clean : 
	@$(RM) *.txt main *.o
