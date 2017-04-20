#ifndef __heap
#define __heap


#include "nod.h"


#ifndef __Heap__struct
#define __Heap__struct

class Heap {

//am explicat in heap.cpp ce face fiecare functie

private:
	int size;
	int dimension;
	Nod** element;	


	int left(const int);
	int right(const int);
	int father(const int); 

	void percolate(int);
	void sift(int);

public:

	int getSize();
	int getDimension();

	void setSize(const int);
	void setDimension(const int);

	void insertHeap(Nod*);
	void deleteHeap(); //va sterge tot timpul nodul din varf=> nu e nevoia sa i se transmita nodul de sters

	bool isEmpty();

	void constructHeap(Input);

	void constructHuffmanTree();

	Nod* getMin();

} ;

#endif


#endif