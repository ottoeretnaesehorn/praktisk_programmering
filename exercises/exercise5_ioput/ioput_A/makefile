CC = gcc
CFLAGS = -O -gnu11 -Wall
LDLIBS = -lm



default : out.txt
	@cat $<

out.txt : read_cmdline
	@./read_cmdline 1 2 3 4 5 > $@

read_cmdline : read_cmdline.o
	@$(CC) $^ -o $@ $(LDLIBS)

read_cmdline.o : read_cmdline.c
	@$(CC) $(CLFAGS) -c $< 



.PHONEY : clean 

clean : 
	@$(RM) read_cmdline *.o
