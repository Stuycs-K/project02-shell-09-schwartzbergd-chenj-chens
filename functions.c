#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "functions.h"

#define STR_BUFFER_SIZE 256
#define ARRAY_SIZE 16
#define TEMPFILE ".tempfile"

// gets the string of the cwd (current working directory)
// - no parameters
// returns a string
char* getdir() {
	char* cwd = (char*) malloc(sizeof(char) * STR_BUFFER_SIZE);
	if (getcwd(cwd, sizeof(char) * STR_BUFFER_SIZE) == NULL){
    printf("Error: %s\n", strerror(errno));
		return NULL;
  }
  return cwd;
}

// shortens abs. path by replacing home path with ~
// - no parameters
// returns shorten directory, a string
// * if cwd is before home, returns regular cwd
char* get_short_cwd() {
  int home_length = strlen(getenv("HOME"));
	char* cwd = getdir();
	if (strlen(cwd) < home_length) {
		return cwd;
	}

	char* shortcwd = (char*) malloc(sizeof(char) * STR_BUFFER_SIZE);
  strcat(shortcwd, "~/");
	strncpy(shortcwd+2, cwd+home_length+1, strlen(cwd));
	shortcwd[strlen(shortcwd)] = '\0';
  return shortcwd;
}

// prints directory
// char* cwd: current working directory
void print_dir(char* cwd) {
	printf("%s$ ", cwd);
	fflush(stdout);
}

// waits for input from stdin using fgets
// - no parameters
// returns a string with newline removed
char* get_input() {
  char* line_buffer = (char*) malloc(STR_BUFFER_SIZE * sizeof(char));
  if (fgets(line_buffer, STR_BUFFER_SIZE-1, stdin) == NULL) {
    return NULL;
  }
  line_buffer[STR_BUFFER_SIZE-1] = '\0';

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

// for piping- executes the command after the pipe after the grandchild process finishes, taking the temporary file as the input
// int forkpid2: the forkpid of the current process
// int pipeIndex: the index of the pipe symbol in the argument array
// char** arg_array: the array for the argument after being split by spaces
void child_process(int forkpid2, int pipeIndex, char** arg_array) {
  int status;
  waitpid(forkpid2, &status, 0);
  redirstdin(TEMPFILE);
  arg_array[pipeIndex] = NULL;
  redir(&arg_array[pipeIndex+1]);
  execvp(arg_array[pipeIndex+1], &arg_array[pipeIndex+1]);
}

// for piping- executes the command before the pipe by making arg_array[pipeIndex] null and redirecting this to a temporary file
// int pipeIndex: the index of the pipe symbol in the argument array
// char** arg_array: the array for the argument after being split by spaces
void grandchild_process(int pipeIndex, char** arg_array) {
  arg_array[pipeIndex] = NULL; // run first command
  redirstdout(TEMPFILE);
  redir(arg_array);
  execvp(arg_array[0], arg_array);
}

// redir(char** arr): takes a char* array (), checks if a > or < symbol exists and redirects appropriately
// char** arr: the argument array (command array after parsing spaces)
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

// redirstdin(char* filename): takes file name as argument, redirects stdin to that file using dup2
// char* filename: the name of the file to redirect stdin to
void redirstdin(char* fileName){
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

// redirstdout(char* fileName): takes file name as argument, redirects stdout to that file using dup2
// char* filename: the name of the file to redirect stdout to
void redirstdout(char* fileName) {
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

// checks if a pipe exists
// char** arr: the argument array (command array after parsing spaces)
int checkforpipe(char** arr){
  int size = 0;
  int pipeIndex = -1;
  while (arr[size]!=NULL) {
    if (!strcmp(arr[size], "|")) {pipeIndex = size;}
    size++;
  }
  return pipeIndex;
}

// deletes the temporary file
// char* file: name of temporary file
void delete_temp(char* file) {
  if (strcmp(file, TEMPFILE)==0) {
    if (remove(TEMPFILE)) {
      perror("Error deleting temp file.");
    }
  }
}

// used purely for cd stuff 
// not included in functions.h
int arr_len(char** str_arr) {
	int len = 0;
	while (str_arr[len] != NULL) {
		++len;
	}

	return len;
}

// change directory manually
// char** arg_array: to check if there is a cd command
void do_cd(char** arg_array) {
	char* dir_to_cd_to;
	if (arg_array[1] == NULL || strcmp(arg_array[1], "~") == 0) {
		dir_to_cd_to = getenv("HOME");
	} else {
		if (arr_len(arg_array) > 2) {
			printf("cd: too many arguments\n"); // shell error, so no errno for this
			return;
		}

		dir_to_cd_to = arg_array[1];
	}

	int success = chdir(dir_to_cd_to);
  if (success == -1) {
		char error_string[STR_BUFFER_SIZE];
    sprintf(error_string, "%s", arg_array[1]);
    perror(error_string);
	} else if (success == 0) {

	}
}
