CC = gcc
CFLAGS = -O -gnu11 -Wall
LDLIBS = -lm



default : out.txt
	@cat $<

out.txt : read_stdin
	@echo 1 2 3 4 5 | ./read_stdin > $@

read_stdin : read_stdin.o
	@$(CC) $^ -o $@ $(LDLIBS)

read_stdin.o : read_stdin.c
	@$(CC) $(CLFAGS) -c $<  



.PHONEY : clean 

clean : 
	@$(RM) read_stdin *.o
