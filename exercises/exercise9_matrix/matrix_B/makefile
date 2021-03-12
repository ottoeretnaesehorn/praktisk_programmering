CC = gcc 
CFLAGS = -O -std=gnu11 -Wall $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs) 



default : out.txt
	@cat $<

out.txt : matrix
	@./$< > $@

matrix : matrix.o
	@$(CC) $< -o $@ $(LDLIBS)  

matrix.o : matrix.c
	@$(CC) $(CFLAGS) $< -c



.PHONEY : clean 

clean : 
	@$(RM) *.txt matrix *.o
