.PHONY: compile clean
compile shell: main.o functions.o
	@gcc -o shell main.o functions.o -Wall
main.o: main.c
	@gcc -c main.c -Wall
functions.o: functions.c functions.h
	@gcc -c functions.c -Wall
clean:
	rm -f *.o shell
