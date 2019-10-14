/*
    Exercício 6 - Listas
    @author: Samuel James
    https://github.com/SAMXPS
    Estrutura de Dados
    Universidade de Brasília, UnB
*/

#include "../doubly_linked_list.c"
#include <stdlib.h>
#include <stdio.h>

typedef struct patient {
    int time;
    int id;
} patient;

void printListA(list_t* list) {
    element_t* aux;
    patient p;

    for (aux = list->first; aux; aux = aux->next) {
        p = *(patient*)(aux->data);
        printf("%d - %d\n", p.time, p.id);
    }
}

void printListB(list_t* list) {
    int i;
    element_t* aux;

    for (i = 0, aux = list->first; aux; aux = aux->next, i++) {
        printf("%d - %d\n", i+1, ((patient*)(aux->data))->time);
    }
}

int main() {

    /*variaveis auxiliares*/
    int a;
    patient p;
    element_t* aux, *aux2;

    /*Crie a lista*/
    list_t* list = createList(sizeof(patient));
    list_t* pref = createList(sizeof(patient));

    /*Leia a lista original */
    p.time = 1;
    while((a=scanf("%d", &(p.id))) && a != EOF) {
        insertLast(list, &p);
        p.time++;
    }

    /*Imprima a fila geral original*/
    printf("Fila geral original\n");
    printListA(list);
    printf("\n");

    /*Extraia a lista preferencial*/
    aux = list->first;
    while(aux) {
        p = *(patient*)(aux->data);
        if (p.id >= 60) {
            insertLast(pref, &p);
            aux2 = aux->next;
            removeElement(list, aux);
            aux = aux2;
        } else {
            aux = aux->next;
        }
    }

    /*Imprima a fila preferencial*/
    printf("Fila preferencial\n");
    printListA(pref);
    printf("\n");

    /*Fila geral atualizada*/
    printf("Fila geral atualizada\n");
    printListA(list);
    printf("\n");

    /*Resultados*/
    printf("Resultado esperado fila preferencial\n");
    printListB(pref);
    printf("\n");

    printf("Resultado esperado fila geral\n");
    printListB(list);

    /*Libere as listas*/
    removeAll(list);
    free(list);

    removeAll(pref);
    free(pref);

    return 0;
}