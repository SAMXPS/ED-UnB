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
	list_t list_t = createList();
    element_t* aux;

	// READ COMMANDS AND INSERT DATA INTO THE LIST

	while (scanf("%c", &opcode) && opcode != END)  {
		if (opcode == REMOVE_FINAL) {
            remove_final(&list_t, &v);
            printf("%d\n", v);
		} else if (opcode == REMOVE_BEGIN){
            remove_begin(&list_t, &v);
            printf("%d\n", v);
        } else {
			scanf("%d", &v);
			switch(opcode) {
				case INSERT_BEGIN:
                    insert_begin(&list_t, v);
				break;
				case INSERT_FINAL:
                    insert_final(&list_t, v);
				break;
				case REMOVE_VAL:
                    printf("%d\n", remove_val(&list_t, v));
				break;
				case REMOVE_POS:
                    remove_pos(&list_t, v, &v);
                    printf("%d\n", v);
				break;
				case CHANGE_FIRST:
                    scanf("%d", &v2);
                    change_first(&list_t, v, v2);
				break;
				case COUNT:
                    printf("%d\n", count(&list_t, v));
				break;
			}
		}
	}

	// PRINT THE LIST
    printf("\n");

    if(list_t.size > 0){
        aux = list_t.first;
        while (printf("%d\n", aux->val) && (aux = aux->next));
        free_list(&list_t);
    }

	return 0;
}

