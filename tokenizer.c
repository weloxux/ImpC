#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

FILE* tokenize(const char* filename) {
	FILE* file;
	FILE* tokens = tmpfile();
	char cur, prev;
	bool str = false, comm = false, lcomm = false; // Flags for strings, comments, and line comments respectively

	if (!(file = fopen(filename, "r"))) {
		panic("File not found");
	}

	while (!feof(file)) {
		prev = cur;
		cur = fgetc(file);

		if (!comm && !lcomm && !str) {
			fputc(cur, tokens);
		} else if (comm) { // Normal comments
			if (cur == "*" && prev == "/") {
				comm = false;
			}
		} else if (lcomm) {
			if (cur == "\n") {
				lcomm = false;
			}
		} else if (str) {
			if (cur == "\"" && prev != "\\") {
				str = false;
			} else {
				fputc(cur, tokens);
			}
		}
	}

	fclose(file);

	return tokens;
}
