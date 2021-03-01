CC = gcc
CFLAGS = -O -std=gnu11 -Wall $(shell gsl-config --cflags)
LDLIBS = -lm $(shell gsl-config --libs)



default : data.txt
	@cat $<

data.txt : integration
	@./$< > $@

integration : integration.o
	@$(CC) $< -o $@ $(LDLIBS)

integration.o : integration.c
	@$(CC) $(CFLAGS) $< -c



.PHONEY : clean 

clean : 
	@$(RM) *.txt integration *.o
