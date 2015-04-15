#include <stdio.h>
#include <stdlib.h>

typedef struct nod{
	int inf;
	struct nod*next;
} nod;


struct om {

	int inaltime;

};
//head e primul nod din lista
struct om x;


nod* inserare_last(nod* head, int x) { //insereaza la final, head e primul nod, trebuie mai itnai sa ajungem la final
	//functia va intoarce intodeauna primul nod (e util in cazul in care stiva e goala si va trebui sa creez un nod nou, trebuie sa si il returnez)
	if(head ==  NULL) { //daca stiva e goala
		nod* nou = malloc(sizeof(nod));
		nou->inf = x;
		nou->next = NULL;
		return nou; 
	}
	else {
	    nod* d = head; //trebuie sa retin primul nod ca sa pot sa il returnez (functia va intoarce mereu primul nod)
		while(head->next != NULL) //ma duc la final
			head = head->next;
		nod* de_adaugat = malloc(sizeof(nod)); //aloc memorie pentru noul nod

		de_adaugat -> inf = x;
		de_adaugat -> next = NULL; //fiind ultimul pointeaza catre NULL
		head->next = de_adaugat;  //head era ultimul meu nod, acum va fi antepenultimul, pointand catre ultimul(de adaugat)

		return d;//returnez primul nod din lista
	 }
}

void sterge_last(nod* head) { //sterge ultimul nod din lista

	while(head -> next -> next != NULL)
		head = head->next;
//am ajuns la ultimul nod
	nod* to_delete = head-> next; //il retin undeva ca sa pot sa ii dau free dupa ce rup legatura
	head->next = NULL; //rup legatura cu el (head era antepenultimul nod)
	free(to_delete); //eliberez si zona de memorie alocata ultimului nod
}

void afis(nod*  head) { 

	while(head != NULL) {
		printf("%d\n" , head->inf );
		head = head-> next;
	}
	printf("\n");
}


int return_last(nod*  head) { //returneaza valoarea de la ultimul nod

	while(head->next != NULL)
		head = head->next;
	return head->inf;
}
 
void adauga(int a, int b) {

	return a + b;
}

void stergere(int x, nod* head) //sterge prima aparitie a nodului cu valoarea x
{
	while(head->next->inf!=x){ //cat timp nu suntem in nodul pe care vrem sa il stergem
		head=head->next;
	}
	if(head->next->next==NULL){ //daca nodul pe care vrem sa il stergem e chiar ultimul
			nod* k=head->next;
			head->next=NULL;
			
			free(k);
	}
	nod* k=head->next; //ca sa pot sa dau free pe el dupa ce il "sterg" scot din lista
	head->next=head->next->next;
	free(k);
}
	
int main()
{
	//x.intaltime=5;
	nod* primul_nod_lista = NULL; //asta va fi tot timpul primul nod lista, cu el retinem lista

	// p->inf = 5;
	//(*p).inf = 7; //le fel, sagetica e scriere prescurtat

	//simulam o stiva
	primul_nod_lista = inserare_last(primul_nod_lista , 4);

	primul_nod_lista = inserare_last(primul_nod_lista, 2);
	primul_nod_lista = inserare_last(primul_nod_lista, 6);
	primul_nod_lista = inserare_last(primul_nod_lista, 7);


	printf("%d\n", return_last(primul_nod_lista)); //da valoarea ultimului element din stiva, adica 7
	sterge_last(primul_nod_lista); //scoatem ultimul element din stiva adica 7
	printf("%d\n", return_last(primul_nod_lista)); // acum o sa returneze 6 ca l-am scos pe 7

	//La coada e foarte asemenator, doar ca in loc sa inseram la finalul liste, vom insera la inceput, scoatem tot ca la stiva de la finalul liste
	//scrie funciile pentru coada ca exercitiu un
	return 0;

}
