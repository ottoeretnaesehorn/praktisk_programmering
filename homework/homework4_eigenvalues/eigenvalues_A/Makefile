CC = gcc
CFLAGS = -Wall -O -std=gnu11 $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)
OBJFILES = main.o jacobi.o printing.o



default : out.txt

out.txt : test 
	@./$< > $@

test : $(OBJFILES)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

main.o : main.c
	@$(CC) $(CFLAGS) -o $@ -c $< 

jacobi.o : jacobi.c
	@$(CC) $(CFLAGS) -o $@ -c $<

printing.o : printing.c
	@$(CC) $(CFLAGS) -o $@ -c $<



.PHONEY	: clean 

clean : 
	@$(RM) *.txt test *.o  
