CC = gcc
CFLAGS = -O -Wall -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
OBJFILES = main.o cubic_spline.o



default : spline.svg spline_integ.svg spline_deriv.svg

spline_deriv.svg : spline_deriv.gpi spline_data.txt
	@gnuplot $<

spline_integ.svg : spline_integ.gpi spline_data.txt
	@gnuplot $<

spline.svg : spline.gpi spline_data.txt points.txt
	@gnuplot $<

spline_data.txt points.txt : main 
	@./$< > $@

main : $(OBJFILES)
	@$(CC) $(CFLAGS) -o $@ $(OBJFILES) $(LDLIBS)

cubic_spline.o : cubic_spline.c
	@$(CC) $(CFLAGS) -c $<

main.o : main.c
	@$(CC) $(CFLAGS) -c $<



.PHONEY : clean 

clean : 
	@$(RM) *.svg *.txt main *.o 
