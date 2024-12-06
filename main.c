#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "functions.h"

// just for testing, no real functionality
void printArr(char** arr) {
	int j = 0;
	do {
		printf("arg %d: '%s'\n", j, arr[j]);
		j++;
	} while(arr[j]!=NULL);
}

int main(int argc, char* argv[]) {
	int forkpid;
	char* input;
	char** cmd_array;
	char** arg_array;
	int stdout = STDOUT_FILENO;
	int stdin = STDIN_FILENO;
	int backup_stdout = dup(stdout);
	int backup_stdin = dup(stdin);

	int iters = 0;
//	while (1) {

        //printf("HOME: %s\n", getenv("HOME"));
		//printf("iters: %d, command line! enter command: ", iters); // remove this later to be just $
		//fflush(stdout);
		//input = get_input(); // will wait until enter
		while (1) {
            printf("%s $ ",getdir());
            input=get_input();
			if (strcmp(input, "exit")==0) {
                exit(1);
            }
		    cmd_array = split(input, ";"); // first split over the semicolons
		    int i = 0;
		    do {
			    // printf("arg %d: '%s'\n", i, cmd_array[i]);
			    arg_array = split(cmd_array[i], " "); // then split over spaces
			    printArr(arg_array);

			    forkpid = fork();
			    if (forkpid == -1) {
				    perror("Failed to fork");
				    return -1;
			    } else if (forkpid == 0) {
				    printf("child here %d!\n", getpid());
				    execvp(arg_array[0], arg_array);
				    return 0;
			    } else {
				    printf("parent here %d!\n", getpid());
				    printf("child pid: %d\n", forkpid);

				    int status;
				    waitpid(forkpid, &status, 0);
				    printf("child exited\n");
			    }

			    free(arg_array);
			    printf("\n");
			    i++;
		    } while(cmd_array[i]!=NULL);

		    free(input);

		    iters++;
    }
	printf("how did you get here?\n");
		// printf("Enter command: ");
		// fflush(stdin);
		// char line_buffer[LINE_BUFFER_SIZE];
		// redirstdin("test.txt");
		// fgets(line_buffer, LINE_BUFFER_SIZE-1, stdin);
		// redirstdout("foo.txt");
		// printf("string you entered (parse later): %s\n", line_buffer);
		// fgets(line_buffer, LINE_BUFFER_SIZE-1, stdin);
		// printf("string 2 you entered (parse later): %s\n", line_buffer);

		// redirstdin("test.txt");
		// char* input = get_input();
		// redirstdout("foo.txt");
		// printf("string you entered (parse later): %s\n", input);
		//
		// char** test_array;


	return 1;
}
