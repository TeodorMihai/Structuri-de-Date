#ifndef __input
#define __input


class Input {

public:

	FILE* in;
	FILE* out;
	FILE* text;

	void openFiles(int, const char**);
	Input();
	char* readText();
};

#endif