#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "functions.h"

#define ARRAY_SIZE 16

int main(int argc, char* argv[]) {
	char* input = get_input();
	printf("string you entered (parse later): %s\n", input);

	char* arg_array[ARRAY_SIZE];
	split(input, arg_array, " ");

	for (int i = 0; arg_array[i+1] != NULL; ++i) {
		printf("%d: %s\n", i, arg_array[i]);
	}

	// execvp(args_array[0], args_array);
	//
	// printf("failed\n");
	// have to split over semicolons
	// treat each semicolon split line as an individia

	return 0;
}
