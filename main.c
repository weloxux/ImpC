#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interpreter.h"

void panic(const char* msg, const int line) {
	if (line == 0) {
		printf("Error: %s.\n", msg);
	} else {
		printf("Error in line %d: %s.\n", line, msg);
	}
	exit(1);
}

int main(int argc, char* argv[]) {
	FILE* program_file;
	char* program;
	long length;
	if (argc < 2) 
		panic("Not enough arguments", 0);
	
	if ((program_file=fopen(argv[1], "rb"))==NULL) {
		panic("Cannot open file", 0);
	}

	fseek(program_file, 0, SEEK_END);					// Scan program to determine filesize
	length = ftell(program_file);
	fseek(program_file, 0, SEEK_SET);
	program = malloc(length);
	if (program) {
		fread(program, 1, length, program_file);
	}
	fclose(program_file);
	//program = malloc((ftell(program_file) * sizeof(char)) + 1);		// Allocate sufficient memory
	//fread(program, sizeof(char), ftell(program_file), program_file);	// Write file into string
	printf("Program: %s", program);

	return interpret(tokenize(program));
}
