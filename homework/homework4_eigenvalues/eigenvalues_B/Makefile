CC = gcc
CFLAGS = -Wall -O -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
OBJFILES = main.o jacobi.o printing.o



default : out.txt eigenvectors.svg

eigenvectors.svg : eigenvectors.gpi data.txt
	@gnuplot $<

out.txt data.txt : particle_in_a_box  
	@./$< 

particle_in_a_box : $(OBJFILES)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

main.o : main.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

jacobi.o : jacobi.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	
printing.o : printing.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	


.PHONEY	: clean 

clean : 
	@$(RM) *.txt *.svg *.o particle_in_a_box 
