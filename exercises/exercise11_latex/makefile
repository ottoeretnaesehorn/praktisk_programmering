CC = gcc
CFLAGS = -O -Wall -std=gnu11
LDLIBS = -lm



default : report.pdf 

report.pdf : report.tex plot.png
	@pdflatex $<
	@pdflatex $<

plot.png : plot.gpi data.txt
	@gnuplot $<

data.txt : main
	@./$< > $@

main : main.o 
	@$(CC) $< -o $@ $(LDLIBS) exponential.h

main.o : main.c
	@$(CC) $(CFLAGS) $< -c



.PHONEY : clean 

clean : 
	@$(RM) *.png *.pdf *.aux *.log *.txt main *.o


