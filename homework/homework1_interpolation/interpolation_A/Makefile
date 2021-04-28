CC = gcc
CFLAGS = -O -Wall -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
OBJFILES = main.o linear_spline.o



default : spline.svg spline_integ.svg

spline_integ.svg : spline_integ.gpi data.txt
	@gnuplot $<

spline.svg : spline.gpi data.txt points.txt
	@gnuplot $<

data.txt points.txt : main
	@./$< > $@

main : $(OBJFILES)
	@$(CC) -o $@ $(OBJFILES) $(LDLIBS)

main.o : main.c linear_spline.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

linear_spline.o : linear_spline.c linear_spline.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<



.PHONEY : clean 

clean : 
	@$(RM) *.svg *.txt main *.o 
