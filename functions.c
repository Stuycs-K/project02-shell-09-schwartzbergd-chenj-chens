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
