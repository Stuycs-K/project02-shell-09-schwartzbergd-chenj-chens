#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "functions.h"

int main(int argc, char* argv[]) {
	char* input = get_input();
	printf("string you entered (parse later): %s\n", input);

	char** cmd_array = split(input, ";"); // first split over the semicolons

	printf("size %d\n", ARRAY_SIZE);
	for (int i = 0; cmd_array[i+1] != NULL; ++i) {
		printf("arg %d: %s\n", i, cmd_array[i]);
		// split(cmd_array[i], arg_array, " "); // then split over spaces
		// for (int j = 0; arg_array[j+1] != NULL; ++j) {
		// 	printf("%d: %s\n", j, arg_array[j]);
		// }
	}
	//
	// char args_array[ARGS_ARRAY_SIZE][LINE_BUFFER_SIZE];
	// split_space(line_buffer, args_array);

	// execvp(args_array[0], args_array);
	//
	// printf("failed\n");
	// have to split over semicolons
	// treat each semicolon split line as an individia

	return 0;
}
