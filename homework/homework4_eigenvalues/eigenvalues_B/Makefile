CC = gcc
CFLAGS = -Wall -O -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
OBJFILES = main.o jacobi.o printing.o



default : out.txt plot.svg
	@cat $<

plot.svg : plot.gpi data.txt
	@gnuplot $<

out.txt data.txt : main  
	@./$< 

main : $(OBJFILES)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

main.o : main.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

jacobi.o : jacobi.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	
printing.o : printing.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	


.PHONEY	: clean 

clean : 
	@$(RM) *.txt *.svg *.o main 
