CC = gcc
CFLAGS = -O -std=gnu11
LDLIBS = -lm



general : out.txt
	@cat $<

out.txt : math
	@./math > $@

math : math.o
	@$(CC) -o $@ $^ $(LDLIBS)

math.o : math.c
	@$(CC) $(CLFAGS) -c $^



.PHONEY : clean 

clean :
	@$(RM) *.o math *.txt
