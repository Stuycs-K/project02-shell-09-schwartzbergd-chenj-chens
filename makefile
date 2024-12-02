.PHONY: compile clean
compile shell: main.o
	@gcc -o shell main.o
main.o: main.c
	@gcc -c main.c
clean:
	rm -f *.o shell
