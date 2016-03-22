impc: main.c flag.h tokenizer.c interpreter.c interpreter.h
	gcc -g -Wall -o impc main.c tokenizer.c interpreter.c -I.
