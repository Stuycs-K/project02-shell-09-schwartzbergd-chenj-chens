#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "functions.h"

int main(int argc, char* argv[]) {
	char* input;
	char** cmd_array;
	char** arg_array;

	int iters = 0;
	while (1) {
		printf("iters: %d, command line! enter command: ", iters); // remove this later to be just $
		fflush(stdout);
		input = get_input(); // will wait until enter
		if (input == NULL) {
			printf("exiting\n");
			exit(0);
		}
		cmd_array = split(input, ";"); // first split over the semicolons
		int i =0;
		do {
			printf("arg %d: %s\n", i, cmd_array[i]);
			arg_array = split(cmd_array[i], " "); // then split over spaces
			int j = 0;
			do {
				printf(" - subarg %d: %s\n", j, arg_array[j]);
				j++;
			} while(arg_array[j]!=NULL);

			free(arg_array);
			printf("\n");
			i++;
		} while(cmd_array[i]!=NULL);

		free(input);

		iters++;
	}
}
