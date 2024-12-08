#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "functions.h"

#define EOF_CHAR 0x04

// testing only 
// intended to print null at the last index
void printArr(char** arr) {
	for (int j = 0; ; ++j) {
		printf("arg %d: '%s'\n", j, arr[j]);
		if (arr[j] == NULL) {
			break;
		}
	}
}

int main(int argc, char* argv[]) {
	char* input;
	char** cmd_array;
	char** arg_array;
	char error_string[BUFFER_SIZE];

	while (1) {
		print_dir(get_short_cwd());

		input = get_input();
		if (input == NULL) {
			return 0;
		}
		
		cmd_array = split(input, ";"); // split over semicolons first
	  for (int i = 0; cmd_array[i] != NULL; i++) {
			arg_array = split(cmd_array[i], " ");
			if (arg_array[0][0] == EOF_CHAR || strcmp(arg_array[0], "exit") == 0) {
				return 0;
			}
			
			if (strcmp(arg_array[0], "cd") == 0) {
        do_cd(arg_array);
        continue;
	    }
	    
    	int forkpid = fork();
  		if (forkpid == -1) {
		    perror("Failed to fork");
		    return 1;
			} else if (forkpid == 0) { // first child
				int pipeIndex = checkforpipe(arg_array);
				if (pipeIndex !=-1) { // if pipe exists
					int forkpid2 = fork(); // then fork
					if (forkpid2 == -1) {
            perror("Failed to fork");
            return 1;
					} else if (forkpid2 == 0) { // grandchild process
            grandchild_process(pipeIndex, arg_array);
						sprintf(error_string, "%s", arg_array[0]);
				    perror(error_string);
						return 1;
					} else {
            child_process(forkpid2, pipeIndex, arg_array);
						sprintf(error_string, "%s", arg_array[0]);
				    perror(error_string);
						return 1;
					}
				}
			
				redir(arg_array);
				execvp(arg_array[0], arg_array);
		    sprintf(error_string, "%s", arg_array[0]);
		    perror(error_string);
				return 1;
		  
			} else { // main program
		    int status;
		    waitpid(forkpid, &status, 0);
		  }
			
			free(arg_array);
		}
		
		free(input);
	} // while loop
	
	printf("Impossible to reach here");
	return 1;
}