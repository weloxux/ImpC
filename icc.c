#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int panic(const char* msg) {
	printf("ERROR %s", msg);
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
	char cur;

	if (argc < 2) {
		panic("Not enough arguments");
	}

	FILE* tokens = tokenize(argv[1]);

	while (!feof(tokens)) {
		cur = fgetc(tokens);
		printf("%c", cur);
	}

	return EXIT_SUCCESS;
}
