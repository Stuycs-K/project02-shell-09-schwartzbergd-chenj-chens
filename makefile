<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 5af1cbf6825bb3fe03fd6c314c59e4f3521a7fc2
.PHONY: compile clean
compile shell: main.o functions.o
	@gcc -o shell main.o functions.o -Wall
main.o: main.c
	@gcc -c main.c -Wall
functions.o: functions.c functions.h
	@gcc -c functions.c -Wall
clean:
	rm -f *.o shell
<<<<<<< HEAD
=======
.PHONY: compile clean
compile shell: main.o functions.o
	@gcc -o shell main.o functions.o
main.o: main.c
	@gcc -c main.c
functions.o: functions.c functions.h
	@gcc -c functions.c
clean:
	rm -f *.o shell
>>>>>>> Jialan
=======
>>>>>>> 5af1cbf6825bb3fe03fd6c314c59e4f3521a7fc2
