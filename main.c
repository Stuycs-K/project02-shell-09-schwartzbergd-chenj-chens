#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "functions.h"

int main(int argc, char* argv[]) {
	int stdout = STDOUT_FILENO;
	int stdin = STDIN_FILENO;
	int backup_stdout = dup(stdout);
	int backup_stdin = dup(stdin);
	// printf("Enter command: ");
	// fflush(stdin);
	// char line_buffer[LINE_BUFFER_SIZE];
	// redirstdin("test.txt");
	// fgets(line_buffer, LINE_BUFFER_SIZE-1, stdin);
	// redirstdout("foo.txt");
	// printf("string you entered (parse later): %s\n", line_buffer);
	// fgets(line_buffer, LINE_BUFFER_SIZE-1, stdin);
	// printf("string 2 you entered (parse later): %s\n", line_buffer);

	redirstdin("test.txt");
	char* input = get_input();
	redirstdout("foo.txt");
	printf("string you entered (parse later): %s\n", input);

	char** cmd_array = split(input, ";"); // first split over the semicolons

	char** arg_array;

	printf("size %d\n", ARRAY_SIZE);
	int i =0;
	do {
		printf("arg %d: %s\n", i, cmd_array[i]);
		arg_array = split(cmd_array[i], " "); // then split over spaces
		int j = 0;
		do {
			printf(" - subarg %d: %s\n", j, arg_array[j]);
			j++;
		} while(arg_array[j]!=NULL);
		printf("\n");
		i++;
	} while(cmd_array[i]!=NULL);

	char** test_array;
	// redir(test_array);

	// testing piper()
	// char line[] = "ls -l -h";
	// char ** args = split( line, " " );
	// piper();
	// execvp(args[0], args);
	// char* inp = get_input();
	// printf("%seee\n", inp);


	return 0;
}
