#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "functions.h"

#define BUFFER_SIZE 256
#define ARRAY_SIZE 16
#define TEMPFILE ".tempfile"

int arr_len(char** str_arr) {
	int len = 0;
	while (str_arr[len] != NULL) {
		++len;
	}
	
	return len;
}

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

// shortens abs. path by replacing home path with ~
// - no parameters
// returns shorten directory, a string
char * shortdir() {
  int leng = strlen(getenv("HOME"));
  char * shortcwd = (char *)malloc(sizeof(char)*1024);
  char * cwd = getdir();
  strcat(shortcwd, "~/");
  strncpy(shortcwd+2, cwd+leng-1, strlen(cwd));
  shortcwd[strlen(cwd)]='\0';
  return shortcwd;
}

// prints directory
// - no parameters
void print_dir() {
  	char* cwd = shortdir(); // needs to be changed for "cd" commands
		printf("%s$ ", cwd);
		fflush(stdout);
}

// change directory manually
// char** arg_array: to check if there is a cd command
void do_cd(char** arg_array) {
	if (arr_len(arg_array) != 2) {
		printf("cd: too many arguments\n"); // shell error, so no errno for this
		return;
	}
	
	if (arg_array[1] == NULL) {
		arg_array[1] = getenv("HOME");
	}
	
  int success = chdir(arg_array[1]);
  if (success == -1) {
		char error_string[BUFFER_SIZE];
    sprintf(error_string, "%s", arg_array[1]);
    perror(error_string);
	} else if (success == 0) {
		
	}
	
}

// split over the command array
// char* input: from get_input
// cmd** cmd_array: buffer to store input from user
// returns char** of split commands

void child_process(int forkpid2, int pipeIndex, char** arg_array) {
  int status;
  waitpid(forkpid2, &status, 0);
  redirstdin(TEMPFILE);
  arg_array[pipeIndex] = NULL;
  redir(&arg_array[pipeIndex+1]);
  execvp(arg_array[pipeIndex+1], &arg_array[pipeIndex+1]);
}

void grandchild_process(int pipeIndex, char** arg_array) {
  arg_array[pipeIndex] = NULL; // run first command
  redirstdout(TEMPFILE);
  redir(arg_array);
  execvp(arg_array[0], arg_array);
}

void delete_temp(char * file) {
  if (strcmp(file, TEMPFILE)==0) {
    if (remove(TEMPFILE)) {
      perror("Error deleting temp file.");
    }
  }
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

// splits a string into substrings over delimiters (usually ; or space)
// - char* string: the string to be split on
// - char* delimiters: the (possibly multiple) delimiters that will be passed into strsep
// returns a char** array with max size ARRAY_SIZE, containing the split strings without the delimiters;
// the index after the last string will be NULL
char** split(char* string, char* delimiters) {
	char** array = (char**) malloc(ARRAY_SIZE * sizeof(char*));
	int i = 0;
	for (char* token; i < ARRAY_SIZE && (token = strsep(&string, delimiters)) != NULL; i++) {
		array[i] = token;
  }
	
	array[i] = NULL;
	array[ARRAY_SIZE-1] = NULL; // safety NULL

	return array;
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
  delete_temp(fileName);
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
