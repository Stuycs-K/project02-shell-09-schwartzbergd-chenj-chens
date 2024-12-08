#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "functions.h"

#define EOF_CHAR 0x04

void printArr(char** arr) {
	int j = 0;
	do {
		printf("arg %d: '%s'\n", j, arr[j]);
		if (arr[j]==NULL){
			break;
		}
		j++;
	} while(1);
}

int main(int argc, char* argv[]) {
	// int backup_stdout = dup(STDOUT_FILENO);
	// int backup_stdin = dup(STDIN_FILENO);
	// char* cwd;
	char* input;
	char** cmd_array;
	char** arg_array;
	char error_string[BUFFER_SIZE];

	while (1) {
		print_dir();

		input = get_input();
		if (input == NULL) { // from file
			printf("EOF, exiting\n");
			return 0;
		}
		
		cmd_array = split(input, ";"); // split over semicolons first
	  for (int i = 0; cmd_array[i] != NULL; i++) {
			arg_array = split(cmd_array[i], " ");
			// printArr(arg_array);
			if (arg_array[0][0] == EOF_CHAR){
				printf("Exiting \n");
				return 0;
			}
			if (strcmp(arg_array[0], "exit") == 0) {
				printf("exiting 2\n");
				return 0;
			}
			
			
			if (strcmp(arg_array[0], "cd") == 0) {
	        cd_check(arg_array);
	        continue; // required to make sure cd isn't tried to be execvp()ed
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
					} else {
            child_process(forkpid2, pipeIndex, arg_array);
        }
			}
			
			redir(arg_array);
			execvp(arg_array[0], arg_array);

	    // only reaches here if execvp fails
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