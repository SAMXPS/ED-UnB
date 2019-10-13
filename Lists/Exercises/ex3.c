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

#include "../linked_list.c"

#define INSERT_BEGIN 'I'
#define INSERT_FINAL 'F'
#define REMOVE_FINAL 'P'
#define REMOVE_BEGIN 'D'
#define REMOVE_VAL 'V'
#define REMOVE_POS 'E'
#define CHANGE_FIRST 'T'
#define COUNT 'C'
#define END 'X'
#define DEBUG 0

int datacmp(data da, data db) {
    return *(int*)da - *(int*)db;
}

int main() {

	char opcode;
	int v, v2;
    int runs = 0;
    unsigned int pos;
	list_t* list = createList(sizeof(int));
    element_t* aux;
    int* p;

    #define bindp(a, b) 0*(a=b) + &a

	// READ COMMANDS AND INSERT DATA INTO THE LIST

	while (scanf("%c", &opcode) && opcode != END && (runs++ < 50))  {
        if (opcode == '\n' || opcode == ' ')
            continue;
		if (DEBUG) printf("Code: %c\n", opcode);
        if (opcode == REMOVE_FINAL) {
            removeLast(list, &v);
            printf("%d\n", v);
		} else if (opcode == REMOVE_BEGIN){
            removeFirst(list, &v);
            printf("%d\n", v);
        } else {
			scanf("%d", &v);
			switch(opcode) {
				case INSERT_BEGIN:
                    insertFirst(list, &v);
				break;
				case INSERT_FINAL:
                    insertLast(list, &v);
				break;
				case REMOVE_VAL:
                    printf("%d\n", removeVal(list, &v, &datacmp));
				break;
				case REMOVE_POS:
                    removeAt(list, &p, (unsigned int) v - 1);
                    printf("%d\n", *p);
                    free(p);
				break;
				case CHANGE_FIRST:
                    scanf("%d", &((*findVal(list, &v, &datacmp, &pos))->val));
				break;
				case COUNT:
                    printf("%u\n", countVal(list, &v, &datacmp));
				break;
			}
		}
        if (DEBUG) printList(list);
    }

	// PRINT THE LIST
    printf("\n");

    if(list->size > 0){
        aux = list->first;
        while (printf("%d\n", aux->val) && (aux = aux->next));
        removeAll(list);
    }

    free(list);

	return 0;
}

