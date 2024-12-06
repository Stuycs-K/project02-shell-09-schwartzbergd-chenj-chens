#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "functions.h"

#define EOF_CHAR 0x04

// just for testing, no real functionality
void printArr(char** arr) {
	int j = 0;
	do {
		printf("arg %d: '%s'\n", j, arr[j]);
		j++;
	} while(arr[j]!=NULL);
}

int main(int argc, char* argv[]) {
	// int backup_stdout = dup(STDOUT_FILENO);
	// int backup_stdin = dup(STDIN_FILENO);
	char* cwd;
	char* input;
	char** cmd_array;
	char** arg_array;
	char error_string[BUFFER_SIZE];


	while (1) {
		cwd = getdir(); // needs to be changed for "cd" commands
		printf("%s$ ", cwd);

    input = get_input();
		if (input == NULL) { // doesn't exactly work for some reason, prints command line when doing ./shell < stdin.txt
			printf("EOF, exiting\n");
			return 0;
		}

    cmd_array = split(input, ";"); // split over the semicolons
		for (int i = 0; cmd_array[i] != NULL; i++) {
			// printf("char 1: %c %d\n", cmd_array[i][0] ,(int)cmd_array[i][0]);
			// exit check
			if (strcmp(cmd_array[i], "exit") == 0) {
				printf("exiting...\n"); // remove in final, keep for testing maybe
				return 0;
			}

	    arg_array = split(cmd_array[i], " "); // then split over spaces

			// cd check
			if (strcmp(arg_array[0], "cd") == 0) {
				int success = chdir(arg_array[1]);
				if (success == 0) {

				} else if (success == -1) {
					sprintf(error_string, "%s", arg_array[1]);
					perror(error_string);
				}

				continue; // required to make sure cd isn't tried to be execvp()ed
			}

			int forkpid = fork();
	    if (forkpid == -1) {
		    perror("Failed to fork");
		    return 1;
	    } else if (forkpid == 0) {
				redir(arg_array);
				// HANDLE REDIRECTION / PIPING HERE
				// "< would go after the first command only,
				// > would go at the end of the command only.
				// e.g. a < c.txt | b  > d.txt "

		    execvp(arg_array[0], arg_array);

				// only reaches here if execvp fails
				sprintf(error_string, "%s", arg_array[0]);
				perror(error_string);

				return 1;
	    } else {
		    int status;
		    waitpid(forkpid, &status, 0);
	    }

	    free(arg_array);
		}

		free(input);
  }

	printf("??? You shouldn't be here, probably\n");
	return 1;
}
