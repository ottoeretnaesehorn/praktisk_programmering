CC = gcc
CFLAGS = -O -std=gnu11 -fwrapv
LDLIBS = -lm



default : out.txt
	@cat $^

out.txt : epsilon
	@./epsilon > $@

epsilon : epsilon.o
	@$(CC) -o $@ $^ $(LDLIBS)

epsilon.o : epsilon.c
	@$(CC) $(CFLAGS) -c $^ 


