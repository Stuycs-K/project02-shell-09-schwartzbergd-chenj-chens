#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>


// doesn't shorten with ~ yet
char * getdir() {
  char * cwd;
  int s = sizeof(char) * 1024;
  cwd = (char *)malloc(s);
  if (getcwd(cwd, s)==NULL){
    printf("Error: %s\n", strerror(errno));
  }
  return cwd;
}
