CC = gcc
CFLAGS = -O -Wall 
LDLIBS = -lm
OBJFILES = main.o ode_rk12.o
OUT = susceptible.txt infectious.txt removed.txt



default : plot.svg
	
plot.svg : plot.gpi $(OUT)
	@gnuplot $<
	
$(OUT) : main
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
