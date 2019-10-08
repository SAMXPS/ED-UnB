#include <stdio.h>
#include <stdlib.h>

// CHANGE THIS FOR OTHER TYPES OF LIST
#define DATA_TYPE int

typedef DATA_TYPE data;

struct _dadot {
    data val;
    struct _dadot* next;
};

typedef struct _dadot element;

struct _list{
	int size;
	element *first;
	element *last;
};

typedef struct _list list;

list getEmptyList() {
    list list = {.size = 0, .first = NULL, .last = NULL};
    return list;
}

int insert_begin(list* b, data val) {
	element* l = malloc(sizeof(list));
	if (l) {
		l->val = val;
		l->next = b->first;
		b->first = l;
		if (! b->last) b->last = l;
		b->size++;
		return 1;
	}
	return 0;
}

int insert_final(list* b, data val) {
	element* l = malloc(sizeof(list));
	if (l) {
		l->val = val;
		l->next = NULL;

		if (b->last){
			b->last->next = l;
		} else {
			b->first = l;
		}

		b->last = l;
		b->size++;
		return 1;
	}
	return 0;
}

int remove_begin(list* b, data* val) {
	element* aux;
	if (b->first) {
		aux = b->first->next;
		*val = b->first->val;
		free(b->first);
		b->first = aux;
		if (!aux) b->last = aux;
        b->size --;
		return 1;
	}
	return 0;
}

int remove_final(list *b,  data* val){
	element* aux;
	if (b->last) {
        *val = b->last->val;
        free(b->last);
		if (b->first == b->last) {
			b->first = NULL;
			b->last = NULL;
		} else {
        	aux = b->first;
			// go to the 'last but one' element
        	while (aux->next != b->last && (aux = aux->next));
        	aux->next = NULL;
        	b->last = aux;
		}
        b->size --;
		return 1;
	}
	return 0;
}

int remove_val(list *b, data val) {
    int count = 0;

    element** aux, *bux, *cux = NULL;
    aux = &(b->first);

    while (*aux) { // TODO: FIX SEGFAULT HERE
        if ((*aux)->val == val) {
            bux = *aux;
            *aux = (*aux)->next;
            free(bux);
            count++;
        } else {
            cux = *aux;
            aux = &(bux->next);
        }
    }

    b->last = cux;
    b->size -= count;

    return count;
}

int remove_pos(list*b, int pos, data* val) {
    if (pos == 0) return remove_begin(b, val);
    if (pos == b->size-1) return remove_final(b, val);

    int i;
    element * aux, **p;

    for (p = &(b->first), i=0; i<pos && *p; i++, p = &((*p)->next));
    if (i==pos) {
        aux = *p;
        if (aux) {
            *val = aux->val;
            *p = aux->next;
            free(aux);
            return 1;
        }
    }
    return 0;
}

int count(const list* const b, const data find) {
    int c = 0;
    element *aux;
    aux = b->first;
    while (aux) {
        if (aux->val == find) c++;
        aux = aux->next;
    }
    return c;
}

int change_first(const list* const b, data v1, data v2) {
    int c = 0;
    element *aux;
    aux = b->first;
    while (aux) {
        if (aux->val == v1) {
            aux->val = v2;
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}


void free_list (list *b) {
    element *aux;
    while ((aux = b->first) != NULL) {
        b->first = aux->next;
        free(aux);
    }
    b->last = NULL;
    b->size = 0;
}

// CODE FOR AN EXERCISE

/*
I Insere no início.
F Insere no final.

P Remove no final e imprime valor removido.
D Remove no início e imprime valor removido.

V Remove por valor e retorna a quantidade de itens removidos.
E Remove por posição e retorna o valor removido.

T Troca o valor da primeira ocorrencia do item pelo valor novo.

C Retorna ocorrencias de valor.

X Indica o final das operações e que a lista resultante deve ser impressa.
*/

#define INSERT_BEGIN 'I'
#define INSERT_FINAL 'F'
#define REMOVE_FINAL 'P'
#define REMOVE_BEGIN 'D'
#define REMOVE_VAL 'V'
#define REMOVE_POS 'E'
#define CHANGE_FIRST 'T'
#define COUNT 'C'
#define END 'X'

int main() {

	char opcode;
	int v, v2;
	list list = getEmptyList();
    element* aux;

	// READ COMMANDS AND INSERT DATA INTO THE LIST

	while (scanf("%c", &opcode) && opcode != END)  {
		if (opcode == REMOVE_FINAL) {
            remove_final(&list, &v);
            printf("%d\n", v);
		} else if (opcode == REMOVE_BEGIN){
            remove_begin(&list, &v);
            printf("%d\n", v);
        } else {
			scanf("%d", &v);
			switch(opcode) {
				case INSERT_BEGIN:
                    insert_begin(&list, v);
				break;
				case INSERT_FINAL:
                    insert_final(&list, v);
				break;
				case REMOVE_VAL:
                    printf("%d\n", remove_val(&list, v));
				break;
				case REMOVE_POS:
                    remove_pos(&list, v, &v);
                    printf("%d\n", v);
				break;
				case CHANGE_FIRST:
                    scanf("%d", &v2);
                    change_first(&list, v, v2);
				break;
				case COUNT:
                    printf("%d\n", count(&list, v));
				break;
			}
		}
	}

	// PRINT THE LIST
    printf("\n");

    if(list.size > 0){
        aux = list.first;
        while (printf("%d\n", aux->val) && (aux = aux->next));
        free_list(&list);
    }

	return 0;
}

