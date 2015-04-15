#include "complex.h"

/*
Complex::Complex(double re, double im) {
	this->re = re;
	this->im = im;
}
*/

//altfel de constructor

Complex::Complex(double real, double imaginar) :
	re(real),
	im(imaginar) {
}

Complex::Complex() {
	this->re = 0;
	this->im = 0;
}


Complex::~Complex() {

}



Complex Complex::conjugate() {

	Complex cnj(this->re, -this->im);
	return cnj;
}

double Complex::getRe() {

	return this->re;
}

double Complex::getIm() {

	return this->im;
}