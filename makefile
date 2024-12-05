.PHONY: compile clean
compile shell: main.o functions.o
	@gcc -o shell main.o functions.o
main.o: main.c
	@gcc -c main.c
functions.o: functions.c functions.h
	@gcc -c functions.c
clean:
	rm -f *.o shell
