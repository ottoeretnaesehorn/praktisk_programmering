CC = gcc 
CFLAGS = -O -std=gnu11

default : out.txt
	@cat $^

out.txt : hello
	@./hello > $@

hello : hello.o
	@$(CC) -o $@ $< 

hello.o : hello.c
	@$(CC) $(CFLAGS) -c $^



.PHONEY : clean

clean : 
	@$(RM) *.txt hello *.o
