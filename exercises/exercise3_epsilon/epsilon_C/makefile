CC = gcc 
CFLAGS = -O -std=gnu11 -Wall 
LDLIBS = -lm



default : out.txt
	@cat $<

out.txt : test
	@./test > $@

test : test.o 
	@$(CC) $^ -o $@ $(LDLIBS)

test.o : test.c equal.h
	@$(CC) $(CFLAGS) -c $< -o $@



.PHONEY : clean 

clean : 
	@$(RM) *.txt test *.o 
