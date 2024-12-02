#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "functions.h"

int main(int argc, char* argv[]) {
  printf("test: %d\n", func(10));

	return 0;
}
