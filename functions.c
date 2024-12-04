#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "functions.h"

/* get_input(): mallocs a string and fgets until stdin newline and returns the string (without newline)
*/

char* get_input() {
  char* line_buffer = (char*) malloc(BUFFER_SIZE * sizeof(char));
  if (fgets(line_buffer, BUFFER_SIZE-1, stdin) == NULL) {
    return NULL;
  }
  line_buffer[BUFFER_SIZE-1] = '\0';

  int newline_check = strlen(line_buffer) - 1;
  if (line_buffer[newline_check] == '\n') {
    line_buffer[newline_check] = '\0';
  }

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
  arg_array[ARRAY_SIZE-1] = NULL;

	return arg_array;
}
