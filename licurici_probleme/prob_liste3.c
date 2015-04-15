#include <stdio.h>
#include <stdlib.h>

#include <string.h>

struct Subprduse {

	char* name;
	double cantitate;
	double pret;
};

struct Produs {

	double pret;
	double cantitate;
	char* name;
	struct Subproduse *sub;
};

struct Categorie{

	char* tip_produs;
	struct Produs* produse;
};
/*
void add_produs(struct Produs** lista, int *nr_produse) {
	
	(*nr_produse)++
	*lista = realloc(*lista, (*nr_produse) * sizeof(struct Produs));

	baga_valori_produs



}
*/
void baga_valori_produs(struct Produs *p, double _cantitate, double _pret, char *_nume) {

	p->name = malloc(strlen(_nume) * sizeof(char) + 1);
	strcpy(p->name, _nume);
	p->pret = _pret;
	p->cantitate = _cantitate;
}

struct Produs cauta_produs(char* _name, struct Produs* lista, int nr_produse) {

	int i ;

	for(i = 0; i < nr_produse; ++i )
		if(strcmp(_name, lista[i].name) == 0)
			return lista[i];
}


void print_produs(struct Produs p) { //afisarea din aia frumoasa

	printf("Nume produs: %-30s  Pret produs: %-20lf Cantitatea produs: %-20lf\n", p.name, p.pret, p.cantitate);
}

int main() {

	struct Produs* lista_produse;
	int nr_produse = 1;
	lista_produse = malloc(nr_produse * sizeof(struct Produs));
	baga_valori_produs(&lista_produse[nr_produse - 1], 345.3453, 766.2342, "pepsi cu aroma de cola");
	
	++nr_produse;
	lista_produse = realloc(lista_produse, nr_produse * sizeof(struct Produs));
	baga_valori_produs(&lista_produse[nr_produse - 1], 10034.234, 9874.2342, "cherrycola");

	++nr_produse;
	lista_produse = realloc(lista_produse,nr_produse * sizeof(struct Produs) );
	baga_valori_produs(&lista_produse[nr_produse - 1], 2.232, 111.34, "cancer");
	int i;
	for(i = 0; i < nr_produse ; ++i)
		print_produs(lista_produse[i]);

	print_produs(cauta_produs("cancer",lista_produse,  nr_produse));
	return 0;
}