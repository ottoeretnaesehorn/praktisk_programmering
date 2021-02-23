CC = gcc
CFLAGS = -O -std=gnu11 -Wall  
LDLIBS = -lm



default : out.txt
	@cat $<

out.txt : read_file input.txt
	@./read_file > $@

read_file : read_file.o
	@$(CC) $< -o $@ $(LDLIBS)

read_file.o : read_file.c
	@$(CC) $(CFLAGS) -c $^



.PHONEY : clean 

clean : 
	@$(RM) out.txt read_file *.o 
