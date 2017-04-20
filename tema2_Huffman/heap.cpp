#include <stdlib.h>
#include <time.h>

#include "heap.h"
#include "nod.h"
#include "huffman.h"

//geters si setersi

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

void Heap::insertHeap(Nod* key) {

	if(this->dimension == 0) { //daca heapul nu are niciun element
		this->element = (Nod**)malloc(sizeof(Nod*) * 2);
		this->dimension = 2;
	}

	if(this->size >= this->dimension - 1 ) { //daca am umplut memoria alocata pentru heap, mai trebuie sa aloc

		this->dimension = this->dimension * 2;
		this->element = (Nod**)realloc(this->element, this->dimension * sizeof(Nod*));
	}
	//pun elementul pe care vreau sa-l adaug la final si il urc pana unde trebuie (percolate)
	this->size++;
	this->element[this->size] = key;
	percolate(this->size);
}


void Heap::deleteHeap() {

	this->element[1] = this->element[this->size]; //stergem nodul intai copiind ultimul nod din heap peste el
	this->size--; // redimensionam
	sift(1); // coboram noul nod din radacina
}


Nod* Heap::getMin() {

	return this->element[1];
}


void Heap::percolate(int index) { //urc nodul de pe pozitia index in arbore daca este nevoie 

	if(index == 1) return ;

	if((*this->element[index]) < (*this->element[father(index)])) {
		(*this->element[index]).swap(this->element[father(index)]);
		percolate(father(index));
	}
}

void Heap::sift(int index) { //coboram nodul cu indicele index jos in arbore daca este mai mare ca unul dintre fii
	//(il schimbam cu cel mai mic dintre fii ca noul tata sa fie mai mic decat cei doi fii)
	int ind = 0;

	if(left(index) <= this->size)
		ind = left(index);

	if(right(index) <= this->size && *this->element[ind] > *this->element[right(index)])
		ind = right(index);//luam cel mai mic key dintre fii lui index
 
	if(ind != 0 && (*this->element[index]) > (*this->element[ind]) ){
		(*this->element[index]).swap(this->element[ind]);
		sift(ind);	
	}
}


void Heap::constructHeap(Input I) {

	this->size = 0;
	this->dimension = 0;

	for(int i = 0 ;i < I.number_elements; ++i) {

		Nod *curent = new Nod(I.elements[i], NULL, NULL);
		insertHeap(curent); //inserez element cu element
	}
}

void Heap::constructHuffmanTree() {

	while(this->size > 1) { //iau ceele mai mcii 2 noduir, le scot din heap, creez un nod (father) care are ca fii aceste 2 noduri
		//apoi inserez noul nod (father in heap), faca asta pana cand raman doar cu on nod in heap

		Nod* nod1 = getMin(); deleteHeap();
		
		Nod* nod2 = getMin(); deleteHeap();

		Nod* father = new Nod(Symbol('0' , (*nod1).getSym().getFrequency() + (*nod2).getSym().getFrequency()), nod1, nod2);
		insertHeap(father);
	}
}

