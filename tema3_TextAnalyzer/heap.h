#ifndef __heap
#define __heap



class Member{

public:

	int nod;
	double dist;

	Member(int, double);
};


class Heap {

//am explicat in heap.cpp ce face fiecare functie

private:
	int size;
	int dimension;
	Member* element;	


	int left(const int);
	int right(const int);
	int father(const int); 

	void percolate(int);
	void sift(int);

public:

	Heap();

	int getSize();
	int getDimension();

	void setSize(const int);
	void setDimension(const int);

	void insertHeap(Member);
	void deleteHeap(); //va sterge tot timpul nodul din varf=> nu e nevoia sa i se transmita nodul de sters

	bool isEmpty();


	Member getMin();

} ;

#endif