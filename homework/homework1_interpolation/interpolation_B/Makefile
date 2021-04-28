CC = gcc
CFLAGS = -O -Wall -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
OBJFILES = main.o quadratic_spline.o



default : spline.svg

spline.svg : spline.gpi spline_data.txt points.txt
	@gnuplot $<

spline_data.txt points.txt : main 
	@./$< > $@

main : $(OBJFILES) 
	@$(CC) -o $@ $(OBJFILES) $(LDLIBS)

main.o : main.c quadratic_spline.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

quadratic_spline.o : quadratic_spline.c quadratic_spline.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<



.PHONEY : clean 

clean : 
	@$(RM) *.svg *.txt main *.o 
