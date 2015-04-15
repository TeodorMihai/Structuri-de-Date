#ifndef __instruction
#define __instruction


char* get_type(char **s) { //scoate tipul : r, w, d, mw, mr

	int cnt = 0;

	char* to_return = malloc(sizeof(char) * 5);

	while(**s != '\0' && !isalpha(**s)) ++(*s);
	
	while(**s != '\0' && isalpha(**s)) to_return[cnt++] = **s, ++(*s);

	to_return[cnt] = '\0';
	return to_return; // returneaza tipul
}

int get_number(char **s) { // returneaza numarul, pentru index si linie, il returneaza

	int number = 0;

	while(**s != '\0' && !isdigit(**s)) ++(*s);
	
	while(**s != '\0' && isdigit(**s)) number = number * 10 + (**s) - '0' , ++(*s);

	return number;
}


Instruction* get_instruction(FILE* in, FILE *out) { // returneaza lista de instructiuni, vor fi mai multe doa rin caz ca este  o comanda de bonus (mr sau mw)

	Instruction* instr = malloc(sizeof(Instruction)); 

	instr[0].type = malloc(sizeof(char) * 4); //pentru tip: r, d, w, mr, mw 
	instr[0].line = instr[0].ind = instr[0].tmp = 0;
	
	char *s = malloc(600000 * sizeof(char)); //aloc 600000 pentru comenzile de bonus care ar putea fi foarte lungi
	// nu e cea mai optima cestie dar merge nu depasesc memoria pe niciun test :)
	
	char* to_free = s; //pentru eliberrarea memoriei
	fgets(s, 600000, in); //citesc linia cu comanda

	char *str = get_type(&s); // retin intr-o variabila auxiliara pentru a elibera apoi memoria
	
	strcpy(instr[0].type, str); //am scos tipul si il inserez in structura
	free(str);

	instr[0].nr = 1; //acest atribut retine cate instructiuni vom avea in comanda, vor fi mai multe doar pentru cazuril de bonus(mr, mw)

	if(strcmp(instr[0].type, "e") == 0) { //daca e comanda end, nu ma trebuie citit nimic 
		free(to_free);
		return instr;
	}
	instr[0].line = get_number(&s); //scoatem linia 
	instr[0].ind = get_number(&s); // scoatem indexul, valabil pentru toate 


	if(strcmp(instr[0].type, "w") == 0) { //daca e write trebuie sa citim si ce scriem la adresa

		int cnt = 0;
		instr[0].code = malloc(sizeof(char) * 6);	//alocam spatiul pentru adresa

		while(*s != '\0' && !isalnum(*s)) ++s; 
		while(*s != '\0' && isalnum(*s)) instr[0].code[cnt++] = *s, ++s;
		//am aflat adresa
		instr[0].code[cnt] = '\0';
		
	}
	//pentru cazurile r, d, nu mai avem nimic de citit, am completat comanda(instructiunea o returnam)


	if(strcmp(instr[0].type, "mr") == 0) { //pentru cazul mr mai trebuie sa citim un numar care ne va zice cate din urmatoarele campuri trebuie citite
		//citim numaruld e cumpari
		int nr = get_number(&s);
		//creem strcturile , in numar de nr
		instr = realloc( instr, (nr + 1) * sizeof(Instruction));	
		instr[0].nr = nr;

		for(int i = 1; i < nr; ++i) {

			instr[i].type = malloc(sizeof(char) * 5); 
			strcpy(instr[i].type, instr[i - 1].type);

			instr[i].line = instr[i - 1].line;
			instr[i].ind =  instr[i - 1].ind + 1; //linia conincide cu cea a intructiunii interioare, indicele creste cu 1(ne mutam pe casuta urmatoare)

			if(instr[i].ind == (1 << (instr[i].line + 4) ) ) { // daca se termina o line
			
				instr[i].line++; //ne mutam pe linia urmatoare
				instr[i].ind = 0; //de la capatul ei
			}
		
		}		
	}

	if(strcmp(instr[0].type, "mw") == 0) {  
		
		int nr = 0; //prima data sa baga prima adresa

		int cnt = 0 ; //ca sa putem citi codul

		instr[0].code = malloc(sizeof(char) * 5);	

		while(*s != '\0' && !isalnum(*s)) ++s;
		while(*s != '\0' && *s != '.' && isalnum(*s)) instr[0].code[cnt++] = *s, ++s;

		instr[0].code[cnt] = '\0';

		while(1) {

			nr++ ; //crestem numarul de adrese citite
			cnt = 0 ; //pentru cod 

			instr = realloc(instr, (nr + 2) * sizeof(Instruction)); //cu fiecare adresa citita se mai creeaza practic o instructiune, alocam memorie pentru ea
			
			instr[nr].line = instr[nr - 1].line; //la fel ca la mr, linia e aceeasi
			instr[nr].ind =  instr[nr- 1].ind + 1; //indexul creste cu 1

			if(instr[nr].ind == (1 << (instr[nr].line + 4) ) ) { //daca se termina linia
		
				instr[nr].line++; //ne mutam pe linia urmatoare
				instr[nr].ind = 0; //de la capatul ei
			}


			instr[nr].type = malloc(4 *sizeof(char));//bagam tipul in fiecare instructiune
			strcpy(instr[nr].type, "mw");

			instr[nr].code = malloc(sizeof(char) * 5);	

			while(*s != '\0' && *s != '.' && !isalnum(*s)) ++s;
			while(*s != '\0' && *s != '.' && isalnum(*s)) instr[nr].code[cnt++] = *s, ++s;

			instr[nr].code[cnt] = '\0'; 

			if(*s == '.' || *s == '\0') {
			
				instr[0].nr = nr;
				break;
			} 
		}
	}
	free(to_free);
	return instr;
}


void printInstruction(Instruction x, FILE* out) { //pentru debugging


	fprintf(out, "type: %s  line: %d  index: %d   time : %d ", x.type, x.line, x.ind, x.tmp );
	if(strcmp(x.type, "w") == 0 || strcmp(x.type, "mw") == 0)
		fprintf(out, "codul:  %s  ", x.code );
	fprintf(out, "\n");
}

#endif