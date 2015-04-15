#include <stdio.h>
#include "complex.h"


int main() {

	Complex number(2, 5);

	Complex* nr = new Complex(4, 4);

	Complex* nr_vec = new Complex[10];

	printf("%lf %lf\n", nr->getRe(), nr->getIm() );
	printf("%lf %lf\n", number.getRe(), number.getIm());
	printf("%lf %lf\n", nr_vec[0].getRe(), nr_vec[0].getIm());

	// for(int i = 0 ;1 < 10; ++i)
	// 	nr_vec[i] = Complex(2, 5);

	delete nr;
	delete[] nr_vec;
	return 0;
}