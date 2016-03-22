#define ID_STRING 10;
#define ID_NAME 11;
#define ID_OPERATOR 12;

struct token {
	int id;
	char* argument;
	struct token* next;
};
