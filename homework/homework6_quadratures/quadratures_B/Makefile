CC = gcc
CFLAGS = -O -Wall -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
OBJFILES = main.o integrate.o
DATA = data_RIA.txt data_CC.txt data_gsl.txt



default : out.txt plot.svg
	@cat $<
	
plot.svg : plot.gpi $(DATA)
	@gnuplot $<

out.txt $(DATA) : main
	@./$< > $@

main : $(OBJFILES)
	@$(CC) -o $@ $^ $(LDLIBS) 

main.o : main.c integrate.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

integrate.o : integrate.c integrate.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<



.PHONEY : clean 

clean : 
	@$(RM) *.txt main *.o
