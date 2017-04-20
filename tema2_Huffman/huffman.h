#ifndef __huffman
#define __huffman

#include <stdio.h>
//inclusa pentru a putea declasa variabila de tip FILE 

class Symbol {

private:
	unsigned char value;
	double frequency;

public:

	unsigned char getValue() const ;
	void setValue(const unsigned char);

	double getFrequency()const ;
	void setFrequency(const double);

	Symbol(unsigned char, double);
	Symbol();

};

class SymbolOutput {

public:

	int lenght;

	bool code[150];

};


class Input {

public:
	const static int ASCII_MAX = 300;
	int number_elements;

	Symbol *elements;
	int count;

	FILE *in;
	FILE *out;

	void openFilesCompress(const char*, const char*); //argv e const char** //deschid fisierele pentru decomprimare
	void openFilesDecompress(const char* , const char*) ; // deschid fisierele pentru decomprimare
	void makeElements();
	void read();
};



#endif