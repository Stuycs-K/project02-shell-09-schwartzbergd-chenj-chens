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
  // printf("%d\n", FILENO);
  // int backup_stdout = dup(FILENO);
  if (fd1<0) err();
  dup2(fd1, FILENO);
  close(fd1);
}
