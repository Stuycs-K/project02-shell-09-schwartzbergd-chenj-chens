#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "functions.h"

#define LINE_BUFFER_SIZE 256

//int main(int argc, char* argv[]) {
//	char* input = get_input();
//	printf("string you entered (parse later): %s\n", input);
//
//	char** cmd_array = split(input, ";"); // first split over the semicolons
//
//	char** arg_array;
//    int ARRAY_SIZE = 50;
//	printf("size %d\n", ARRAY_SIZE);
//	int i =0;
//	do {
//		printf("arg %d: %s\n", i, cmd_array[i]);
//		arg_array = split(cmd_array[i], " "); // then split over spaces
//		int j = 0;
//		do {
//			printf(" - subarg %d: %s\n", j, arg_array[j]);
//			j++;
//		} while(arg_array[j]!=NULL);
//		printf("\n");
//		i++;
//	} while(cmd_array[i]!=NULL);
//	//
//	// char args_array[ARGS_ARRAY_SIZE][LINE_BUFFER_SIZE];
//	// split_space(line_buffer, args_array);
//
//	// execvp(args_array[0], args_array);
//	//
//	// printf("failed\n");
//	// have to split over semicolons
//	// treat each semicolon split line as an individia
//
//	return 0;
//}

 int main(int argc, char* argv[]) {
 	printf("%s $ ",getdir());
    char * n;
    while(n=get_input()) {
        strcmp(n, "exit\n");    
}

// 	// printf("Enter command: ");
// 	fflush(stdin);
// 	char line_buffer[LINE_BUFFER_SIZE];
// 	while (fgets(line_buffer, LINE_BUFFER_SIZE-1, stdin)) {
// 		if (strcmp(line_buffer, "exit\n")) {
// 			printf("string you entered (parse later): %s\n", line_buffer);
// 		}
// 	}
// 	// printf("return value of fgets: %s\n", n);
//
//
 	return 0;
 }
