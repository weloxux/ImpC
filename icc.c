#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int panic(const char* msg) {
	printf("ERROR %s", msg);
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		panic("Not enough arguments");
	}

	FILE* tokens = tokenize(argv[1]);

	while (!feof(tokens)) {
		printf("%s", fgetc(tokens));
	}

	return EXIT_SUCCESS;
}
