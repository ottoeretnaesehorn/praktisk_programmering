CC = gcc
CFLAGS = -O -std=gnu11 -Wall $(shell gsl-config --cflags) 
LDLIBS = -lm $(shell gsl-config --libs)
OBJFILES = main.o ode_rk12.o



default : plot.svg
	
plot.svg : plot.gpi data.txt
	@gnuplot $<
	
data.txt : main
	@./$< > $@

main : $(OBJFILES)
	@$(CC) -o $@ $^ $(LDLIBS)

main.o : main.c ode_rk12.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $< 

ode_rk12.o : ode_rk12.c ode_rk12.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<



.PHONEY : clean 

clean : 
	@$(RM) main *.o *.txt *.svg 
