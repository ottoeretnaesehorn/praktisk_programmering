default : out.txt
	@cat out.txt

out.txt : hello.exe
	@./hello > $@

hello.exe : hello.o
	@gcc -o $@ $^ 

hello.o : hello.c
	@gcc -c hello.c



.PHONEY : clean

clean : 
	@rm *.txt *.exe *.o
