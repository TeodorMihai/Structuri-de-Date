#include <stdlib.h>
#include <time.h>

#include "heap.h"

//geters si setersi


Member::Member(int nod, double dist) {

	this->dist = dist;
	this->nod = nod;
}


void swap(Member *A, Member* B) {

	Member aux = *A;
	*A = *B;
	*B = aux;
}

int Heap::getSize() {
	return this->size;
}

int Heap::getDimension() {

	return this->dimension;
}


void Heap::setSize(const int size) {
	this->size = size;
}

void Heap::setDimension(const int dimension) {
	this->dimension = dimension;
}
//pentru heap
int Heap::father(const int x){return x/2;}
int Heap::left(const int x) {return x * 2;}
int Heap::right(const int x) {return x * 2 + 1;}


bool Heap::isEmpty() {

	if(this->size == 0)
		return true;
	return false;
}

void Heap::insertHeap(Member key) {

	if(this->dimension == 0) { //daca heapul nu are niciun element
		this->element = (Member*)malloc(sizeof(Member) * 2);
		this->dimension = 2;
	}

	if(this->size >= this->dimension - 1 ) { //daca am umplut memoria alocata pentru heap, mai trebuie sa aloc

		this->dimension = this->dimension * 2;
		this->element = (Member*)realloc(this->element, this->dimension * sizeof(Member));
	}
	//pun elementul pe care vreau sa-l adaug la final si il urc pana unde trebuie (percolate)
	this->size++;
	this->element[this->size] = key;
	percolate(this->size);
}


void Heap::deleteHeap() {

	this->element[1] = this->element[this->size]; //stergem nodul intai copiind ultimul element din heap peste el
	this->size--; // redimensionam
	sift(1); // coboram noul nod din radacina
}


Member Heap::getMin() {

	return this->element[1];
}


void Heap::percolate(int index) { //urc nodul de pe pozitia index in arbore daca este nevoie 

	if(index == 1) return ;

	if(this->element[index].dist < this->element[father(index)].dist ) {
		swap(&this->element[index], &this->element[father(index)]);
		percolate(father(index));
	}
}

void Heap::sift(int index) { //coboram nodul cu indicele index jos in arbore daca este mai mare ca unul dintre fii
	//(il schimbam cu cel mai mic dintre fii ca noul tata sa fie mai mic decat cei doi fii)
	int ind = 0;

	if(left(index) <= this->size)
		ind = left(index);

	if(right(index) <= this->size && this->element[ind].dist > this->element[right(index)].dist)
		ind = right(index);//luam cel mai mic key dintre fii lui index
 
	if(ind != 0 && this->element[index].dist > this->element[ind].dist ){
		swap(&this->element[index], &this->element[ind]);
		sift(ind);	
	}
}

Heap::Heap() {

	this->size = this->dimension = 0;
}