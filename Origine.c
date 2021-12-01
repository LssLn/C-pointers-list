#include <stdio.h>
#include <string.h>
#include <stdlib.h> //serve per malloc


//tipo di interesse = dominio di base
typedef struct s_studente {
	char nome[128]; //nome e cognome
	char matricola[16];
	char cf[17]; //16 + \0
}t_studente;

//lista contenente tipo di interesse e puntatori agli elementi successivi
typedef struct s_nodo_lista_studente {
	t_studente info; //elemento
	struct s_nodo_lista_studente* next; //puntatore al prossimo nodo
}t_nodo_lista_studente;

//}t_nodo_lista_studente, *t_lista_studente;
typedef t_nodo_lista_studente* t_lista_studente;  //è il puntatore alla testa della lista
// equivale a dire riga sopra, cioè o lo definisco così o insieme al t_nodo_lista_studente


//inserimento (lunga) mi entra una lista e ne esce un altra, ma posso passare direttamente lista in con puntatore e modificarla direttamente
//void inserimento(t_lista_studente lista_in, t_studente s, t_lista_studente * p_lista_out);
t_lista_studente* inserimento(t_lista_studente* p_lista, t_studente s) { //è uguale a quella sopra ma più concisa
	t_lista_studente p_aux = NULL;
	//uguale a dire t_nodo_lista_studente * p_aux = NULL;

	p_aux = (t_nodo_lista_studente*)malloc(sizeof(t_nodo_lista_studente));
	if (p_aux == 0) {
		printf("errore allocazione");
		return 0;
	}
	p_aux->info = s;
	/* *p_lista = p_aux;
		p_aux->next = *p_lista; 
		COSI P_AUX PUNTA A SE STESSO*/
	p_aux->next = *p_lista;
	*p_lista = p_aux;
	return p_aux;
} 
//NON VOID!!

void cancella_testa(t_lista_studente* p_lista) { //qui non serve s
	if (*p_lista == NULL)
		return 0;
	t_lista_studente vecchia_radice = *p_lista;
	*p_lista = (*p_lista)->next; //se plist NULL => violazione d'accesso => if null return
	free(vecchia_radice);
}

//funzione di esistenza : vede se s è presente (ritorna boolean)
int esiste(t_lista_studente p_lista, t_studente s) { //non *p_lista perchè è solo visita, non modifico nulla
	t_lista_studente p_aux = p_lista;
	while (p_aux != NULL) { //scorro la lista
		if (strcmp(s.matricola, p_aux->info.matricola) == 0) {
			return 1;
		}
		else p_aux = p_aux->next;
	}
	return 0;
}

//funzioni di comparazione (tornano valori booleani) 0 se ok, < se a<b , > se a>b
int cmp_matricola(t_studente a, t_studente b) {
	return strcmp(a.matricola, b.matricola);
}
int cmp_cf(t_studente a, t_studente b) {
	return strcmp(a.cf, b.cf);
}
int cmp_nome(t_studente a, t_studente b) {
	return strcmp(a.nome, b.nome);
}

t_lista_studente* inserimento_ordinato(t_lista_studente* p_lista, t_studente s) {
	
	if (*p_lista == NULL) { //se lista vuota, fa solo inserimento normale
		return inserimento(p_lista, s);
	}
	if (cmp_nome(s, (*p_lista)->info)<0) {
		// *plista è puntatore al puntatore, deferenzia (cioè arrivo alla radice)  cioè mi fa avere lista non p_lista
		//perchè a cmp_nome non serve passare un puntatore, solo la lista.. siccome qui nei parametri introduco un p_lista
		return inserimento(p_lista, s);
	} //cioè è il più piccolo elemento -> lo metto in testa e sposto il resto
	//se non si verificano i primi due, allora non è al primo posto-> scorro la lista 
	/*
	t_lista_studente tail = (*p_lista)->next;
	t_nodo_lista_studente* testa = *p_lista;
	li devo inserire nella riga successiva
	*/
	inserimento_ordinato(&((*p_lista))->next, s);
	// ]]] *plista contiene il puntatore alla radice della lista. ]]] ->next è il tail della lista. ]]] & perchè devo accedervi e usarlo
	//cioè scorre la coda finquando non si ha cmp_nome < 0 

	//se s è 25, e ho la lista 10 20 30 40 50, scorre fino ad arrivare a 30 (2 cicli) e così esegue l'if di cmp_nome.

}

void ordinamento(t_lista_studente* p_lista) {
	t_lista_studente lista_ordinata_temporanea = NULL;
	t_lista_studente p_aux = *p_lista; //radice della lista in ingresso, non puntatore della radice, perchè è **
	t_studente studente;
	while (p_aux != NULL) {
		studente = p_aux->info; //testa alla lista in ingresso che inserisco
		inserimento_ordinato(&lista_ordinata_temporanea, studente);
		//qui se volessi potrei mettere la funzione cancella testa (&p_aux) e così non mi serve la parte di cancella dopo
		p_aux = p_aux->next;
	}

	//---- da qui
	p_aux = *p_lista;
	while (p_aux != NULL) {
		cancella_testa(&p_aux);
	}
	p_aux = NULL;
	//---- a qui serve a non sprecare memoria, cioè mi resterebbe questa lista aux piena e inutile

	*p_lista = lista_ordinata_temporanea;
}

int main() {
	t_lista_studente lista = NULL;
	t_studente studente;

	if (inserimento(&lista, studente) == NULL) { //&lista perchè devo modificare (era definito come * nella funzione)
		printf("errore inserimento");
	}

	cancella_testa(&lista);

	scanf("%s", studente.matricola);
	esiste(lista, studente);

}
