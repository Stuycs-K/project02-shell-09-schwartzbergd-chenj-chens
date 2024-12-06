#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#define BUFFER_SIZE 256
#define ARRAY_SIZE 16

char * getdir() {
  char * cwd;
  int s = sizeof(char) * 1024;
  cwd = (char *)malloc(s);
//  long l = strlen(getenv("HOME"))
  if (getcwd(cwd, s)==NULL){
    printf("Error: %s\n", strerror(errno));
  }
  return cwd;
}

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

//old
//char* get_input() {
//  int BUFFER_SIZE = 256;
//  printf("%s $ ",getdir());
//  fflush(stdin);
//  char* line_buffer = (char*) malloc(BUFFER_SIZE * sizeof(char));
//  fgets(line_buffer, BUFFER_SIZE-1, stdin); line_buffer[BUFFER_SIZE-1] = '\0';
//  return line_buffer;
//}

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

// err(): prints errno
int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

// redirstdout(char * fileName): takes file name as argument, redirects stdout to that file using dup2
void redirstdout(char * fileName){
  fflush(stdout);
  int fd1 = open(fileName, O_WRONLY|O_TRUNC|O_CREAT, 0644);
  int FILENO = STDOUT_FILENO;
  if (fd1<0) err();
  dup2(fd1, FILENO);
  close(fd1);
}

// redirstdin(char * filename): takes file name as argument, redirects stdin to that file using dup2
void redirstdin(char * fileName){
  fflush(stdin);
  int fd1 = open(fileName, O_RDONLY);
  int FILENO = STDIN_FILENO;
  if (fd1<0) err();
  dup2(fd1, FILENO);
  close(fd1);
}

// redir(char** arr): takes an array (command array after parsing spaces), and redirects appropriately based on symbol
void redir(char** arr){
  int size = 0;
  while (arr[size]!=NULL) size++;
  if (!strcmp(arr[size-2], "<")){
    redirstdin(arr[size-1]);
  }
  if (!strcmp(arr[size-2], ">")){
    redirstdout(arr[size-1]);
  }
}

// pipe(): redirects stdout to temp and redirects stdin to temp, (haven't done) removes temp file after
void piper(){
//  int backup_stdout = dup(STDOUT_FILENO);
  redirstdout("temp.txt");
//  dup2(backup_stdout, STDOUT_FILENO); // set stdout entry to original
  redirstdin("temp.txt");
  //if (remove("temp.txt")<0) err();
}
