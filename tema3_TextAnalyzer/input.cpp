#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "input.h"

Input::Input() {

	this->in = this->out = this->text = NULL;
}


void Input::openFiles(int argc, const char** argv) {

	this->in = fopen(argv[1],"r");
	this->out = fopen(argv[2], "w");

	char *text_file = new char[60];

	fgets(text_file, 60, this->in);

	text_file[strlen(text_file) - 1] = '\0'; //sa scapam de newline
	this->text = fopen(text_file, "r");

	delete[] text_file;

}

char* Input::readText() {

	//aflam cate caracetre sunt in fisier
	fseek(this->text, 0, SEEK_END); 
	int sizeFile = ftell(this->text);
	
	rewind(this->text);

	char *str = new char[sizeFile + 1];

	fread(str, sizeof(char), sizeFile, this->text );

	return str;
}

