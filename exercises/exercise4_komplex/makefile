CC = gcc 
CFLAGS = -O -std=gnu11 -Wall 
LDLIBS = -lm



default : test
	@./test 

test : test.o 
	@$(CC) $^ -o $@ $(LDLIBS)

test.o : test.c komplex_with_functions.h komplex.h
	@$(CC) $(CFLAGS) -c $< -o $@



.PHONEY : clean 

clean : 
	@$(RM) *.txt test *.o 
