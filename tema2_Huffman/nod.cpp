#include "nod.h"



Nod::Nod(Symbol sym, Nod* st, Nod* dr) {

	this->sym = sym;
	this->left = st;
	this->right = dr;
}

bool Nod::operator <(const Nod& nod) const {

	return this->sym.getFrequency() < nod.sym.getFrequency();
}

bool Nod::operator >(const Nod& nod) const {  //orice obiect constant poate apela doar functii constante asa ca a trebuit  sa fac functiile de get constante


	return this->sym.getFrequency() > nod.sym.getFrequency();
}

void Nod::swap(Nod* x) {

	Nod aux = *x;
	*x = *this;
	*this = aux;
}


Symbol Nod::getSym() const {

	return this->sym;
}

void Nod::setSym(const Symbol sym) {
	this->sym = sym;
}