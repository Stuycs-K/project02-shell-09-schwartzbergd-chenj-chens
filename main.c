#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "functions.h"

#define LINE_BUFFER_SIZE 256

 int main(int argc, char* argv[]) {
    char * n;
    printf("HOME: %s\n", getenv("HOME"));
    while(n=get_input()) {
        if (strcmp(n, "exit\n")==0 || strcmp(n, "\n")==0) {
            exit(1);
        }
    }
 	return 0;
 }
