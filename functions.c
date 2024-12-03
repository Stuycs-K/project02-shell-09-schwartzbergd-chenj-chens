#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define LINE_BUFFER_SIZE 256
#define ARRAY_SIZE 16

char* get_input() {
  printf("Enter command: ");
  fflush(stdin);
  char* line_buffer = (char*) malloc(LINE_BUFFER_SIZE * sizeof(char));
  fgets(line_buffer, LINE_BUFFER_SIZE-1, stdin); line_buffer[LINE_BUFFER_SIZE-1] = '\0';

  return line_buffer;
}

/*
split_space: takes a string and splits over spaces, returns the array of the strings
*/

void split_space(char* string, char** arg_array) {
  char* token;
  int i;
  while ((token = strsep(&string, " ")) != NULL) {
    arg_array[i] = token;
    i++;
  }
  arg_array[i] = NULL;
}
