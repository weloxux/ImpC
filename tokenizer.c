#include "flag.h"
#include "token.h"
#include <string.h>
#include <stdio.h> // TEMP

char** tokenize(const char* program) {
	const char* startnamechars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	const char* allnamechars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-_";
	int pindex = 0;
	int tindex = 0;
	int line = 1;
	int i;
	flag string = OFF;
	flag name = OFF;
	flag prev = OFF;

	for (i = 0; i < strlen(program); i++) {
		if (string == ON) {	// String mode
			if (program[pindex] == "\"" && program[pindex - 1] != "\\") {
				string = OFF;
				tindex++;
			} else if (program[pindex] == "\n") {
				panic("Illegal newline in string", line);
			} else {
				strcat(tokens[tindex], program[pindex]);
			}
		} else {		// Normal mode
			switch (program[pindex]) {
			case '\"':
				string = ON;
				tokens[tindex] = "STR_";
			case ';':
				tindex++;
				name = OFF;
			case '\n':
				line++;
			case '/':
				tokens[tindex] = "ODV_";
				tindex++;
			default: // Variable names
				if (name == ON) {
					if (strchr(allnamechars, program[pindex])) {
						strcat(tokens[tindex], program[pindex]);
					} else {
						panic("Illegal character in variable name", line);
					}
				} else {
					if (strchr(startnamechars, program[pindex])) {
						name = ON;
						prev = FNC;
						//tindex++;
						tokens[tindex] = "VAR_";
					} else {
						panic("Illegal character in non-variable position", line);
					}
				}
			}
		}
		pindex++;
	}
	
	return tokens;
}
