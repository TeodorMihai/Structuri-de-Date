#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <iostream>
#include <string.h>

#include "heap.h"
#include "nod.h"
#include "huffman.h"


typedef struct TagHuffmanNode{

	unsigned char value;
	int16_t left;
	int16_t right;

} __attribute__((__packed__))__TagHuffmanNode;


unsigned int find_number_nodes(Nod* curent) { //calculez numarul total de noduri

	if(curent == NULL) return 0;

	return find_number_nodes(curent->left) + find_number_nodes(curent->right) + 1;

}


void traverse(int *count,  Nod* root) { //ca sa asociezi fiecarui nod din arborele huffman cate un indice in mod unic(bijectiv)


	root->ind = *count;

	if(root->left != NULL) {
		(*count)++;
		traverse(count, root->left);
	}
	

	if(root->right != NULL) {
		(*count)++;
		traverse(count, root->right);
	}
}

void DFS(Nod* root, TagHuffmanNode* HNodes) { //pentru testare nevermind

	if(root == NULL) return ;

	DFS(root->left, HNodes);
	DFS(root->right, HNodes);
}

void getIndex(TagHuffmanNode* HNodes, Nod* root) { //asociezi indexul pentru vectorul de structuri tagHuffmanNoDES asa cum precizeaza tema
	//pe baza indexului asociat anteroior(in functia traverse)

	if(root->left == NULL && root->right == NULL) {

		HNodes[root->ind].left = -1; //cand e frunza nu are fii
		HNodes[root->ind].right = -1;
		HNodes[root->ind].value = root->getSym().getValue();
		return;
	}

	if(root->right != NULL && root->left != NULL) {
		HNodes[root->ind].left = root->left->ind; //nodul actual are ca fii indicele nodului din stanga/dreapta
		HNodes[root->ind].right = root->right->ind;
		getIndex(HNodes, root->left);//merg mai departe in tot arborele
		getIndex(HNodes, root->right);
		return ;
	}

}


void getCaracter(int cnt, int *stiva, SymbolOutput *caracter, Nod* root)  {  // asociez fiecarui caracter codul corespuzator folosind o stiva
	//pentru a retine codul (de la radacina la frunza, drumul va fi codul, 0 - stanga, 1 -dreapta)

	if(root->left != NULL){
		
		stiva[cnt] = 0;
		getCaracter(cnt + 1, stiva, caracter, root->left);
	} 
	//practic am 1 pe muchia dreapta si 0 pe muchia stanga

	if(root->right != NULL) {

		stiva[cnt] = 1;
		getCaracter(cnt + 1, stiva, caracter, root->right);
	}

	if(root->left == NULL && root->right == NULL) { //cand am ajuns in frunza bag codul in structura corespunzatoare caracaterului
		//vezi structur SymbolOutput din fisierul huffman
		//printf("%d\n", (int)root->getSym().getValue());

		caracter[(int)root->getSym().getValue()].lenght =  cnt; //cati biti are codificarea caracetrului respectiv

		for(int i = 0; i < cnt; ++i)
			caracter[(int)root->getSym().getValue()].code[i] = stiva[i];
	}
}


void print(unsigned char x, SymbolOutput* caracter) { //pentru debug

	for(int i = 0 ;i < caracter[(int)x].lenght; ++i)
		printf("%d  ", caracter[(int)x].code[i]);
}


void printt(Input I, SymbolOutput* caracter) {

	unsigned char c;
	const int LENGHT_MAX = 10000000;
	unsigned char v[LENGHT_MAX];
	//creez un vector de unsigned char-uri ca sa afisez datele comprimate asa cum se specifica in tema
	//bag bit cu bit in vector apoi afisez tot vectorul deodata
	int cnt = 0 ; int bit = 7;

	for(int k = 0 ;k < I.count; ++k) {

		c = fgetc(I.in);

		for(int i = 0; i < caracter[(int)c].lenght; ++i) {

			if(bit == -1) {
				bit = 7;
				cnt++;
			}

			if(caracter[(int)c].code[i])
				v[cnt] = v[cnt] + (1 << bit);
			bit--;
		}

	}
	std::cout << "There were: " << I.count  << " bytes in the initial file and now there are: " <<   cnt << " bytes + additional metatada (instruction for decompression)." << '\n'; 

	fwrite(v, sizeof(unsigned char), (cnt + 1), I.out);
}

void compress(Heap H, Input I) {

	H.constructHuffmanTree(); //construiesc arborele huffman
	int number_char = I.count;
	int number_nodes = find_number_nodes(H.getMin());

	fwrite(&number_char, sizeof(uint32_t), 1, I.out);
	fwrite(&number_nodes, sizeof(uint16_t), 1, I.out);
	//aflu numarul de noduri si de caractere
	TagHuffmanNode *HNodes = new TagHuffmanNode[number_nodes];
	
	int cnt = 0;
	
	traverse(&cnt, H.getMin()); //ascoiezi indicii
	
	getIndex(HNodes, H.getMin()); //creezz structuril TagHuffmanNode asa cum se cere in tema

	DFS(H.getMin(), HNodes);
	
	fwrite(HNodes, sizeof(TagHuffmanNode), number_nodes, I.out); //scriu nodurile

	const int ASCII_MAX = 300;
	const int ADANCIME_MAX = 150;

	SymbolOutput caracter[ASCII_MAX]; //ascoiezi fiecarui caracter cate un cod

	int stiva[ADANCIME_MAX];

	getCaracter(0, stiva, caracter, H.getMin());

	rewind(I.in);//parcurg din nou fisierul de intrare ca sa asociezi fiecarui caracter un cod si sa.l scriu in fisier
	printt(I, caracter);	

	fclose(I.in); fclose(I.out);
}

unsigned char getChar(unsigned char *v, int *ind, int *bit , TagHuffmanNode* HNodes, int index_node) { //pentru decompresie


	if(HNodes[index_node].left == -1) //cand sunt in frunza returnez caracterul cu codul cerut
		return HNodes[index_node].value;

	if(*bit == -1) { //ca sa decodific codul din vecoturl de charuri 
		(*ind)++;
		(*bit) = 7;
	}

	if(v[*ind] & (1 << (*bit))) {
		(*bit)--;
		return getChar(v,ind, bit , HNodes, HNodes[index_node].right);

	} else {

		(*bit)--;
		return getChar(v, ind, bit,   HNodes, HNodes[index_node].left);

	}

}


void decompress(Input I) {

	uint32_t number_char; uint16_t number_nodes;

	fread(&number_char, sizeof(uint32_t), 1, I.in);
	fread(&number_nodes, sizeof(uint16_t), 1, I.in);

	TagHuffmanNode *HNodes = new TagHuffmanNode[number_nodes];
	fread(HNodes, sizeof(TagHuffmanNode), number_nodes, I.in);
	
	//aflu care caractere am de decodificat
	int first = ftell(I.in);

	fseek(I.in, 0, SEEK_END);

	int last = ftell(I.in);
	int len = last - first;

	fseek(I.in, first, SEEK_SET);


	unsigned char v[1000000];

	fread(v, sizeof(unsigned char), len, I.in);
	
	int ind = 0 ;int  bit = 7;

	for(unsigned i = 0 ;i < number_char; ++i) //la fiecare caracter pornesc din radcina si am duc in functie de cum imi zice codifcarea
		//in dreapta sau in stanga pana ajung la o frunza unde se afla caracterul pe care vreau sa il scriu
		fprintf(I.out, "%c",getChar(v,&ind, &bit, HNodes, 0));

}


int main(int argc, char const *argv[]) {
	/* code */

	Input I;
	
	if(argv[1][1] == 'c') {

		I.openFilesCompress(argv[2], argv[3]);
		I.read(); //citesc datele

		Heap H;
    	H.constructHeap(I); //creez heapul
		compress(H, I);
	}
	
	
	if(argv[1][1] == 'd')  {
		I.openFilesDecompress(argv[2], argv[3]);
		decompress(I);
	}

	return 0;
}