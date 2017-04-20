#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>


#include "graph.h"


Pair::Pair() {

	this->nod = 0;
	this->cost = 0;
}

Pair::Pair(int nod, double cost) { //constructor pentru muchie 

	this->nod = nod;
	this->cost = cost;
}



Node::Node() { 

	this->frequency = 0;

	for(int i = 0; i < 128; ++i)
		this->son[i] = NULL;
}

void Graph::getWords(char* str) { //scot cuvintele

	char *delimeters = new char[30];
	char* separators = new char[30];

	this->root = new Node;

	strcpy(delimeters, "!.,?\":();_*!$%&^");
	strcpy(separators, " -\n");

	this->numberWords = 0; //numaru cuvinte
	this->numberWordsU = 0;//numar cuvinte unice

	char *pch = NULL;
	pch = strtok(str, separators);
	
	while(pch != NULL) {

		//sterg simbolurile din delimteres
		for(unsigned i = 0 ; i < strlen(delimeters); ++i) {

			char *p = strchr(pch, delimeters[i]);
			while(p != NULL) {

				strcpy(p , p + 1);
				p = strchr(pch, delimeters[i]);
			}
		}

		//transform literele mari in litere mici
		for(unsigned  i = 0 ;i < strlen(pch) ; ++i)
			if(pch[i] >= 'A' && pch[i] <= 'Z')
				pch[i] = tolower(pch[i]);

		words[this->numberWords++] = strdup(pch);

		if(insertWord(root, pch, &this->numberWordsU) == 0)  {//daca cuvantul nu a mai fost intalnit, il bag in vectorul de cuvinte unice
			words_u[this->numberWordsU - 1] = strdup(pch);
		}		

		pch = strtok(NULL, separators);
	}
}


int Graph::getId(Node* curent, char* str) { //1 daca cuvantul exista deja, obtin id-ul(nodul) corespunzator fiecarui cuvant

	if(*str == '\0' || *str == '\n') 
		return curent->index;

	if(curent->son[(int)*str] == NULL)
		printf("EROARE se cauata cuvant in tree neintrodus");

	return getId(curent->son[(int)*str], str + 1);

}


int Graph::insertWord(Node* curent, char* str, int* index) { //1 daca cuvantul exista deja

	if(*str == '\0' || *str == '\n') { 
		curent->frequency++; //de cate ori apare cuvantul

		if(curent->frequency == 1){ //daca nu a mai aparut inainte
			curent->index = (*index); //asociez un index cuvantului
			(*index)++; //cresc numarul de cuvinte unice

			return 0;
		}

		return 1;
	}

	if(curent->son[(int)*str] == NULL) {

		curent->son[(int)*str] = new Node;
	}

	return insertWord(curent->son[(int)*str], str + 1, index);//ma duc mai jos in tree
}



void Graph::setCosts() {

	double cost[this->numberWords]; double costMax = -1000000000000;

	std::vector<Pair> viz[this->numberWordsU]; //ca sa nu calculez de doua ori acelasi cost

	for(int i = 0 ;i < this->numberWords - 1; ++i) {

		char* word1 = strdup(this->words[i]);
		char* word2 = strdup(this->words[i + 1]);

		int x = getId(this->root, this->words[i]);
		int y = getId(this->root, this->words[i + 1]);
		int ok = 0;

		for(unsigned j = 0 ;j < viz[x].size(); ++j)
			if(viz[x][j].nod  == y) {
				cost[i] = viz[x][j].cost;
				ok = 1;
			}

		if(ok) continue; //am mai calculat costul pentru aceasta sintagma odata

		int O11 = 0; int O22 = 0; int O12 = 0; int O21 = 0; //au aceeasi semnificatie ca cea din enuntul textului

		for(int j = 0 ;j < this->numberWords - 1; ++j) {

			if(strcmp(this->words[j], word1) == 0) {

				if(strcmp(this->words[j + 1], word2) == 0) 

					O11++;
				else 
					O12++;

			} else if(strcmp(this->words[j + 1], word2) == 0)
					O21++;
				else 
					O22++;

		}

		cost[i] = log(1.0 * O11 + 0.5) + log(1.0 * O22 + 0.5) - log(1.0 * O12 + 0.5) - log(1.0 * O21 + 0.5); // formula din enunt

		if(costMax < cost[i]) //costul maxim, pentru formula
			costMax = cost[i];

		viz[x].push_back(Pair(y, cost[i]));
	}

	for(int i = 0 ;i < this->numberWords - 1; ++i) {
		
		int x = getId(this->root, this->words[i]);
		int y = getId(this->root, this->words[i + 1]);

		P[x].push_back(Pair(y, 1 + costMax - cost[i]));	//adaug muchia, chia r daca se baga aceeasi muchie de doua ori nu e problema

	}

}


