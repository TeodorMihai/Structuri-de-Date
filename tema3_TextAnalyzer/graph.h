#ifndef __graph
#define __graph

#include <vector>


class Node {

public:

	int frequency;
	int index;
	Node *son[128];

	Node();

};


class Pair {


public:

	int nod;
	double cost;

	Pair();
	Pair(int, double);

};

class Graph {

public:

	static const int MAX_WORDS = 90000;
	static const int MAX_WORDS_UNIQUE = 9000;

	char* words[MAX_WORDS];
	char* words_u[MAX_WORDS_UNIQUE];

	int numberWordsU;
	int numberWords;

	Node *root; //pentru a retine tree-ul

	std::vector<Pair> P[MAX_WORDS];

	void getWords(char*);


	int constructGraph();
	int insertWord(Node*, char*, int*);
	int getId(Node*, char*);

	void setCosts();
};






#endif


