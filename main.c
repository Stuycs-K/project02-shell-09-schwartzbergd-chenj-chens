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
	char* cwd;
	char* input;
	char** cmd_array;
	char** arg_array;
	int forkpid;

	int iters = 0;
	while (1) {
		cwd = getdir(); // needs to be changed for "cd" commands
		printf("%s$ ", cwd);
		
    input = get_input();
		if (strcmp(input, "exit") == 0) {
			printf("exiting...\n"); // remove in final, keep for testing maybe
			exit(0);
    }
		
    cmd_array = split(input, ";"); // split over the semicolons
		for (int i = 0; cmd_array[i]!=NULL; i++) {
			// printf("arg %d: '%s'\n", i, cmd_array[i]);
	    arg_array = split(cmd_array[i], " "); // then split over spaces
	    printArr(arg_array);

	    forkpid = fork();
	    if (forkpid == -1) {
		    perror("Failed to fork");
		    return -1;
	    } else if (forkpid == 0) {
		    execvp(arg_array[0], arg_array);
					
				// only reaches here if execvp fails
				char error_string[BUFFER_SIZE];
				sprintf(error_string, "%s", arg_array[0]);
				perror(error_string);
				
				return 1;
	    } else {
		    int status;
		    waitpid(forkpid, &status, 0);
		    printf("child exited\n");
	    }

	    free(arg_array);
	    printf("\n");
		}

    free(input);

		iters++; // not needed technically
  }
	printf("how did you get here?\n");
	return 1;
}
