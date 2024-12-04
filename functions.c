#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "functions.h"

int func(int num) {
  return num;
}


int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

// takes file name as argument, redirects stdout to that file
void redir(char * fileName){
  int fd1 = open(fileName, O_WRONLY|O_TRUNC|O_CREAT, 0611);
  int FILENO = STDOUT_FILENO;
  // int backup_stdout = dup(FILENO);
  if (fd1<0) err();
  dup2(fd1, FILENO);
  close(fd1);
}

// takes file name as argument, redirects stdin from that file
void redirstdin(char * fileName){ // not working-- file also becomes empty
  int fd1 = open(fileName, O_WRONLY|O_TRUNC|O_CREAT, 0611); // not sure if file should be created if it doesn't exist
  int FILENO = STDIN_FILENO;
  // printf("%d\n", FILENO);
  if (fd1<0) err();
  dup2(FILENO, fd1);
  close(fd1);
}
