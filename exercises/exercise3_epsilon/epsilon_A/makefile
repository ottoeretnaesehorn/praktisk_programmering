CC = gcc
CFLAGS = -O -std=gnu11 -fwrapv
LDLIBS = -lm



general : out.txt
	@cat $<

out.txt : max_int min_int epsilon
	@./max_int > $@
	@echo "\n" >> $@
	@./min_int >> $@
	@echo "\n" >> $@	
	@./epsilon >> $@
	@echo "\n" >> $@	
	@echo "The epsilon values have only been calculated using one type of loop, since they are equivalent, and it takes quite som time to run them\n" >> $@	



max_int : max_int.o
	@$(CC) -o $@ $^ $(LDLIBS)

max_int.o : max_int.c
	@$(CC) $(CFLAGS) -c $<



min_int : min_int.o
	@$(CC) -o $@ $^ $(LDLIBS)

min_int.o : min_int.c
	@$(CC) $(CFLAGS) -c $<



epsilon : epsilon.o
	@$(CC) -o $@ $^ $(LDLIBS)

epsilon.o : epsilon.c
	@$(CC) $(CFLAGS) -c $<



.PHONEY : clean 

clean : 
	@$(RM) *.txt max_int min_int epsilon *.o  
