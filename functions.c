#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "functions.h"

char* get_input() {
  printf("Enter command: ");
  fflush(stdin);
  char* line_buffer = (char*) malloc(BUFFER_SIZE * sizeof(char));
  fgets(line_buffer, BUFFER_SIZE-1, stdin); line_buffer[BUFFER_SIZE-1] = '\0';

  return line_buffer;
}

/*
split: takes a string and splits over the delimiters, returns the array of the strings
*/

char** split(char* string, char* delimiters) {
	char** arg_array = (char**) malloc(ARRAY_SIZE * sizeof(char*));
  // char* token;
	int i = 0;
	for (char* token; i < ARRAY_SIZE && (token = strsep(&string, delimiters)) != NULL; i++) {
    arg_array[i] = token;
  }
  arg_array[i] = NULL;

	return arg_array;
}


int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

// takes file name as argument, redirects stdout to that file
void redir(char * fileName){
  int fd1 = open(fileName, O_WRONLY|O_TRUNC|O_CREAT, 0644);
  int FILENO = STDOUT_FILENO;
  if (fd1<0) err();
  dup2(fd1, FILENO);
  close(fd1);
}

// takes file name as argument, redirects stdin from that file
void redirstdin(char * fileName){ // not working-- file also becomes empty
  int fd1 = open(fileName, O_RDONLY); // not sure if file should be created if it doesn't exist
  int FILENO = STDIN_FILENO;
  if (fd1<0) err();
  dup2(fd1, FILENO);
  close(fd1);
}
