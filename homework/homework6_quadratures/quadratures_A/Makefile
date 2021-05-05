CC = gcc
CFLAGS = -O -Wall -std=gnu11
LDLIBS = -lm
OBJFILES = main.o integrate.o



default : out.txt
	@cat $<
	
out.txt : main
	@./$< > $@

main : $(OBJFILES)
	@$(CC) -o $@ $^ $(LDLIBS) 

main.o : main.c integrate.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

integrate.o : integrate.c integrate.h
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<



.PHONEY : clean 

clean : 
	@$(RM) *.txt main *.o
