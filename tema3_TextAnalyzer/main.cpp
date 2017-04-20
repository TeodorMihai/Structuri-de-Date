#include <stdio.h>	
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "graph.h"
#include "heap.h"



int main(int argc, char const *argv[]) {
	/* code */

	Input I;

	I.openFiles(argc, argv); //deshid fisierele

	Graph G;

	G.getWords(I.readText()); //scot cuvinte, construiesc tree-ul

	G.setCosts(); //construiesc graful folosind std::vector

	int test1;

	fscanf(I.in, "%d", &test1);
	
	while(test1--) {

		char* word1 = new char[200];
		char* word2 = new char[200];

		fscanf(I.in, "%s", word1);
		fscanf(I.in, "%s", word2);

		int x = G.getId(G.root, word1); //nodul asociat unui cuvant are un id
		int y = G.getId(G.root, word2);

		for(unsigned i = 0 ; i < G.P[x].size(); ++i) //gasesc muchia intre cele 2 noduri
			if(G.P[x][i].nod == y) {
				fprintf(I.out, "%0.7lf\n",G.P[x][i].cost );
				break;
			}
	}

	int test2;

	fscanf(I.in, "%d", &test2); 

	while(test2--) {

		char* word1 = new char[200];
		char* word2 = new char[200];

		fscanf(I.in, "%s", word1);
		fscanf(I.in, "%s", word2);


		int N = G.numberWordsU;

		double dist[N]; int parent[N];


		for(int i = 0 ;i < N; ++i) {
			parent[i] = i;
			dist[i] = 100000000; //initial distanta la oricare alt nod in afara de sursa e inf, un numar mare
		}
		//indicele nodurilor in graf
		int start = G.getId(G.root, word1); 
		int end = G.getId(G.root, word2);

		dist[start] = 0;
		//initial in heap nu am decat un nod, cel de start
		Heap H;
		H.insertHeap(Member(start, 0));

		parent[start] = start;

		while(!H.isEmpty()) { //cat timp as mai putea actualiza un cost pentru un nod

			Member M = H.getMin(); //selectez minimul, il sterg din heap
			H.deleteHeap();
			int nodMin = M.nod;

			for(unsigned j = 0 ; j < G.P[nodMin].size() ; ++j) {

				int x = G.P[nodMin][j].nod;
				
				if(dist[nodMin] + G.P[nodMin][j].cost < dist[x]) { //daca minimul + muchia imbunatatesc distanta pana la nodul x o actulizez
					dist[x] = dist[nodMin] + G.P[nodMin][j].cost;

					H.insertHeap(Member(x, dist[x])); //mai bag noduri in heap
					parent[x] = nodMin;

				}
			}
		}

		//afisare

		int path[300];

		path[0] = 0;

		do {
			path[++path[0]] = end;
			end = parent[end];
		} while(end != parent[end]);

		fprintf(I.out, "%s ", G.words_u[start]);
		while(path[0] > 0 ) {

			if(path[0] != 1)
				fprintf(I.out, "%s ", G.words_u[ path[ path[0] ] ]);
			else 
				fprintf(I.out, "%s", G.words_u[ path[ path[0] ] ]);

			path[0]--;
		}
		fprintf(I.out, "\n");
		

	}
	
	int test3;


	fscanf(I.in, "%d", &test3);

	while(test3--) { //dinamica 

		int len; 
		char *word = new char[200];

		fscanf(I.in, "%d %s", &len, word);




		int N = G.numberWordsU;

		Pair D[N][21];

		//D[i][j].cost - costul celui mai ieftin drum cu sfarsitul in nodul i, de lungime j
		//D[i][j].nod - ultimul nod al celui mai scrut drum, nu i

		std::vector<Pair> Gt[N]; //graful transpus


		for(int i = 0 ; i < N; ++i) { //construiesc graful transpus
			for(unsigned j = 0 ;j < G.P[i].size(); ++j) {

				int x = i;
				double cost = G.P[i][j].cost;
				int y = G.P[i][j].nod;
				Gt[y].push_back(Pair(x, cost));

			}
		}

		//initialiare dinamica, explicat in readme

		for(int i = 0 ;i < N; ++i) {


			double dmin = 1000000000;
			int nodMin;
			
			for(unsigned j = 0 ;j < Gt[i].size(); ++j)
				if(Gt[i][j].cost < dmin) {

					nodMin = Gt[i][j].nod;
					dmin = Gt[i][j].cost;
				}
			D[i][1].nod = nodMin;
			D[i][1].cost = dmin;
		}

		//dinamica propriu-zisa
		

		for(int k = 2; k <= len; ++k) {

			for(int i = 0 ;i < N; ++i) {
				
				D[i][k].cost = 1000000000;

				for(unsigned j = 0 ;j < Gt[i].size(); ++j) {
					int x = Gt[i][j].nod;
					double cost = Gt[i][j].cost;

					if(cost + D[x][k - 1].cost < D[i][k].cost) {
						D[i][k].cost = cost + D[x][k - 1].cost;
						D[i][k].nod = x;
					}

				}
				//mai jos am scris formula de recurenta pe care o apic pentru dinamica
				//D[i][k] = min(D[vecini[i]][k - 1] + cost[vecin[i]][i]);
			}
		}

		int last = G.getId(G.root, word);

		int path[50];

		path[0] = 0;
		//afisare

		while(len > 0) {

			path[ ++path[0] ] = last;
			last = D[last][len].nod;
			len--;
		}

		fprintf(I.out, "1\n");
		while(path[0]) {

			fprintf(I.out, "%s ",G.words_u[path[ path[0]] ] );

			path[0]--;
		}
		fprintf(I.out, "\n");

	}


	return 0;

}