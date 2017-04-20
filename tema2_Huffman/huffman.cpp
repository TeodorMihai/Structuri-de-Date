#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <math.h>
#include "huffman.h"

void Input::read() {

	int convert_ascii[ASCII_MAX];

	this->number_elements = 0;
	this->count = 0;

	for(int i = 0; i < ASCII_MAX ; ++i)
		convert_ascii[i] = 0;

	unsigned char c;
	
	fseek(this->in, 0, SEEK_END);
	
	this->count = ftell(this->in);
	fseek(this->in, 0, SEEK_SET);
	//aflu numarul de caracatere din fisier apoi citesc caracter cu caracter

	for(int k = 0;k < this->count; ++k) {

		c = fgetc(this->in);

		convert_ascii[(int)c]++; //convert_ascii[x] imi spune de cate ori apare caracterul x in fisier
	}

	
	for(int i = 0 ;i < ASCII_MAX; ++i)
		if(convert_ascii[i])  
			this->number_elements++; //vad cate caracatere am

	this->elements = new Symbol[this->number_elements]; //aloc memorie fix pentru cate simboluri am

	int cnt = 0;
	for(int i = 0 ;i < ASCII_MAX ; ++i)
		if(convert_ascii[i]) {

			this->elements[cnt].setValue(i);
			this->elements[cnt++].setFrequency(1.0 * convert_ascii[i] / (1.0 * this->count) );//setez freceventele fiecarui caracter
		}

}

void Input::openFilesCompress(const char *str1, const char* str2) { //fisiere pentru compresie

	this->in = fopen(str1, "r");
	this->out = fopen(str2, "wb");
	//fclose(this->out);
}

void Input::openFilesDecompress(const char *str1, const char* str2) { //fisiere pentru decompresie

	this->in = fopen(str1, "rb");
	this->out = fopen(str2, "w");
}


//geters si sters
unsigned char Symbol::getValue() const {
	return this->value;
}

void Symbol::setValue(const unsigned char value) {
	this->value = value;
}

double Symbol::getFrequency() const{
	return this->frequency;
}

void Symbol::setFrequency(const double frequency) {

	this->frequency = frequency;
}

Symbol::Symbol(unsigned char value, double frequency) {//construcutri OOP 
	this->value = value;
	this->frequency = frequency;
}

Symbol::Symbol() {

	this->value = '0';
	this->frequency = 0;
}


