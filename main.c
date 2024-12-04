#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "functions.h"

#define LINE_BUFFER_SIZE 256

int main(int argc, char* argv[]) {
	printf("Enter command: ");
	fflush(stdin);
	char line_buffer[LINE_BUFFER_SIZE];
	fgets(line_buffer, LINE_BUFFER_SIZE-1, stdin);
	redir("foo.txt");
	printf("string you entered (parse later): %s\n", line_buffer);


	return 0;
}
