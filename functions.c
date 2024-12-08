#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#define BUFFER_SIZE 256
#define ARRAY_SIZE 16

// gets the string of the cwd (current working directory)
// - no parameters
// returns a string
char * getdir() {
  char * cwd;
	int s = sizeof(char) * BUFFER_SIZE;
  cwd = (char *)malloc(s);
//  long l = strlen(getenv("HOME"))
  if (getcwd(cwd, s)==NULL){
    printf("Error: %s\n", strerror(errno));
  }
  return cwd;
}

// waits for input from stdin using fgets
// - no parameters
// returns a string with newline removed
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

int chdir_wrapper(char* newdir) {
	if (newdir == NULL) {
		return chdir(getenv("HOME"));
	} else {
		return chdir(newdir);
	}
}

void exec_wrapper(char** arg_array) {
	execvp(arg_array[0], arg_array);
}

// splits a string into substrings over delimiters (usually ; or space)
// - char* string: the string to be split on
// - char* delimiters: the (possibly multiple) delimiters that will be passed into strsep
// returns a char** array with max size ARRAY_SIZE, containing the split strings without the delimiters;
// the index after the last string will be NULL
char** split(char* string, char* delimiters) {
	char** arg_array = (char**) malloc(ARRAY_SIZE * sizeof(char*));
	int i = 0;
	for (char* token; i < ARRAY_SIZE && (token = strsep(&string, delimiters)) != NULL; i++) {
    arg_array[i] = token;
  }
  arg_array[i] = NULL;
	arg_array[ARRAY_SIZE-1] = NULL; // safety NULL

	return arg_array;
}

// redirstdout(char * fileName): takes file name as argument, redirects stdout to that file using dup2
void redirstdout(char * fileName) {
  fflush(stdout);
  int fd1 = open(fileName, O_WRONLY|O_TRUNC|O_CREAT, 0644);
  int FILENO = STDOUT_FILENO;
	if (fd1 == -1) {
		perror("Failed to redirect stdout");
		return;
	}
  dup2(fd1, FILENO);
  close(fd1);
}

// redirstdin(char * filename): takes file name as argument, redirects stdin to that file using dup2
void redirstdin(char * fileName){
  fflush(stdin);
  int fd1 = open(fileName, O_RDONLY);
  int FILENO = STDIN_FILENO;
	if (fd1 == -1) {
		perror("Failed to redirect stdin");
		return;
	}
  dup2(fd1, FILENO);
  close(fd1);
}

// redir(char** arr): takes a char* array (command array after parsing spaces), checks if a symbol exists and redirects appropriately
//
void redir(char** arr){
  int size = 0;
  int endOfArg = 0;
  while (arr[size]!=NULL) size++;
  if (size<3) return;
  if (!strcmp(arr[size-2], "<") || !strcmp(arr[size-2], ">")){
    if (!strcmp(arr[size-2], "<")){
      redirstdin(arr[size-1]);
      endOfArg = size-2;
    }
    else if (!strcmp(arr[size-2], ">")){
      redirstdout(arr[size-1]);
      endOfArg = size-2;
    }
    arr[endOfArg] = NULL;
    // execvp(arr[0], arr); // not needed?
  }
}

int checkforpipe(char ** arr){
  int size = 0;
  int pipeIndex = -1;
  while (arr[size]!=NULL) {
    if (!strcmp(arr[size], "|")) {pipeIndex = size;}
    size++;
  }
  return pipeIndex;
}
