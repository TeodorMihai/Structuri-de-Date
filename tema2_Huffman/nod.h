#ifndef __Nod
#define __Nod

#include "huffman.h"

class Nod {

private:

	Symbol sym;

	
public:
	Nod* left;
	Nod* right;
	int ind;

	Nod(Symbol, Nod*, Nod*);

	Symbol getSym() const;

	void setSym(const Symbol);

	bool operator <(const Nod&) const ; //functiilor din obiecte li se transmite automat parametrul this, asa ca poti supraincarca operatori
	//binari cu un singur argument

	bool operator >(const Nod&) const ;

	void swap(Nod*);

};

#endif