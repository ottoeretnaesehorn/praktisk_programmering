CC = gcc
CFLAGS = -O -Wall -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
OBJFILES = main.o bilinear.o printing.o



default : plot.svg

plot.svg : plot.gpi out.txt data.txt
	@gnuplot $<

out.txt data.txt : main
	@./$< > $@

main : $(OBJFILES)
	@$(CC) -o $@ $^ $(LDLIBS)

main.o : main.c bilinear.h printing.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

bilinear.o : bilinear.c bilinear.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

printing.o : printing.c printing.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<



.PHONEY : clean 

clean : 
	@$(RM) *.svg *.txt main *.o
