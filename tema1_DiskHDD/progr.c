#include "declaration.h"
#include "stiva.h"
#include "instruction.h"
#include "coada.h"
#include "lista_hard.h"



void execute_command(NodHard* nod, Instruction instr, FILE* out) { /* execut comanda, adaug damageul de comanda */


	if(strcmp(instr.type, "mr") == 0 || strcmp(instr.type, "r") == 0) { 
	
		fprintf(out, "%s\n", get_address(nod->adr));
		nod->damage += READ_DATA;
	}

	if(strcmp(instr.type, "w") == 0 || strcmp(instr.type, "mw") == 0) {

		_NodHard(nod, nod->ind, nod->line, nod->damage, instr.code);
		nod->damage += WRITE;
	}


	if(strcmp(instr.type, "d") == 0) {

		fprintf(out, "%d\n", nod->damage);
		nod->damage += READ_DAMAGE;
	}

}

void calculate_use(NodHard* p, int max_lines, FILE* out) {

	while( ! (p->ind == 0 && p->line == 0) )
		move_toward(&p, 0 , 0);

	int cnt = 4; int first = 0 ; int second = 0; int third = 0; int fourth = 0;
	int total = 0;

	for(int i = 0 ; i < max_lines; ++i) {
		
		int value = (1 << cnt);
		int quarter = value / 4; /* ca sa vad in ce cadran ma aflu */
		
		for(int j = 0 ; j < value; ++j) {

			if(j < quarter) first += p->damage;
			if(j >= quarter && j < quarter * 2 ) second += p->damage;
			if(j >= quarter * 2 && j < quarter * 3) third += p-> damage;
			if(j >= quarter * 3) fourth += p->damage;
			if(p->next != NULL)
				p = p->next;
		}
		total += value;
		if(p->up != NULL)
			p = p->up;

		cnt++;
	}

	total /= 4;

	double rounding = 0.004999999; /*Fac o smecherie ca sa nu ma mai complic cu functiile din math.h, nu-mi plac */

	fprintf(out, "%.2lf %.2lf %.2lf %.2lf\n", 1.0 * first/ total - rounding , 1.0 * second/total - rounding, 1.0 * third / total - rounding, 1.0 * fourth/total - rounding);
}



void rez_coada(FILE *in, FILE* out, int max_lines) {


	 NodHard *p = NULL;
	 Nod* head = NULL;
	 Nod* end = NULL;
	 
	 p = create_list(max_lines); /* Creez hardul */

	 int next_read = 0; 

	while(1) {


		if(next_read == 0) {

			fgetc(in); fgetc(in);
			
			Instruction *x = get_instruction(in, out); /* Citesc instructiunea, este pointer pentru ca la bonus voi avea mai multe instructiuni */

			if(strcmp(x[0].type, "e") != 0) 
				fscanf(in, "%d", &x[0].tmp);
		
			fgetc(in);

			for(int i = 0 ;i < x[0].nr; ++i) 
				push_coada(&head, &end, x[i]); /* Inserez toate instructiunile(mai mutle in caz de bonus) in coada */
 
			next_read = x[0].tmp;

			free(x);
		}
		
		if(!isEmpty_coada(head)) { /* Cat timp mai am instructiuni in coada o iau pe cea cu prioritatea cea mai mare si 
			daca sunt in casuta unde trebuie sa o execut fac asta(execute_command), daca nu, ma duc spre aceasta(move_toward) */

			Instruction execute = peek_coada(head);

			if(strcmp(execute.type, "e") == 0)
				break;

			if(p->ind == execute.ind && p->line == execute.line) {

				execute_command(p, execute, out);
				pop_coada(&head);

			} else 
				move_toward(&p, execute.ind, execute.line);	
		} 

		p->damage++; // aplic damage pe casuta in care sunt, indiferent daca am executat sau nu vreo comada*/
		next_read--; // pentru citirea urmatoarei comenzi
	}

	calculate_use(p, max_lines, out); //calculez uzura
}


void rez_stiva(FILE* in, FILE* out, int max_lines) {


	 NodHard *p = NULL;
	 Nod* head = NULL;
	 
	 p = create_list(max_lines); // creez hard-ul

	 int next_read = 0;

	while(1) {
		
		if(next_read == 0) {
			
			fgetc(in); /* Scap de newline */ fgetc(in);

			Instruction* x = get_instruction(in, out); /* citesc instructiunea, este pointer pentru bonus, voi avea avea mai multe instructiuni */

			if(strcmp(x[0].type, "e") != 0) {
				fscanf(in, "%d", &x[0].tmp);
			} else break; //am citit end m-am oprit

			for(int i = x[0].nr - 1 ;i >= 0; --i) 
				push_stiva(&head, x[i]); /* Inserez totate instructiunile in stiva */

			fgetc(in);
			next_read = x[0].tmp; /*Timpul pana la care voi citit urmatoarea coamanda */
			free(x);

		}
		
		if(!isEmpty_stiva(head)) { /* Cat timp stiva nu e goala execut comanda daca sunt la locul potrivit sau ma mut cu o casuta spre aceasta */

			Instruction execute = peek_stiva(head);

			if(strcmp(execute.type, "e") == 0)
				break;

			if(p->ind == execute.ind && p->line == execute.line) {

				execute_command(p, execute, out); //executat comanda
				pop_stiva(&head); // o scot din stiva

			} else {
				move_toward(&p, execute.ind, execute.line);	 // ma mut spre casuta unde trebuie executata comanda cu prioritatea cea mai amre

			}
		} 

		next_read--;
		p->damage++;

	}

	calculate_use(p, max_lines, out); // calculez uzura

}

int main(int argc, char *argv[]) {

	FILE* in = fopen(argv[1], "r");
	FILE* out = fopen(argv[2], "w");

	int cs; int max_lines;

	fscanf(in, "%d", &cs); //case , stiva sau coada
	fscanf(in, "%d", &max_lines); 
	//numele functiilor sunt sugestive
	if(cs == 1) rez_coada(in, out, max_lines);

	if(cs == 2) rez_stiva(in, out, max_lines);


	return 0;

}