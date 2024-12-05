#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

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

char* get_input() {
  int BUFFER_SIZE = 256;
  printf("%s $ ",getdir());
  fflush(stdin);
  char* line_buffer = (char*) malloc(BUFFER_SIZE * sizeof(char));
  fgets(line_buffer, BUFFER_SIZE-1, stdin); line_buffer[BUFFER_SIZE-1] = '\0';
  return line_buffer;
}
