CC = gcc 
CFLAGS = -O -std=gnu11 -Wall 
LDLIBS = -lm



default : test
	@./test 

test : test.o 
	@$(CC) $^ -o $@ $(LDLIBS)

test.o : test.c name_of_digit.h
	@$(CC) $(CFLAGS) -c $< -o $@



.PHONEY : clean 

clean : 
	@$(RM) *.txt test *.o 
