
//#ifndef __complex
//#define __complex

class Complex {

private:
	double re;
	double im;

public:
	//consructor 
	Complex(double re, double im);
	Complex();
	//destructor	
	~Complex();

	double getRe();
	double getIm();

	Complex conjugate();
};