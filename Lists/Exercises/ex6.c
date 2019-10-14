/*
Lista Duplamente Encadeada - Implementação
@author: Samuel James
https://github.com/SAMXPS
Universidade de Brasília, UnB
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> /* for memcpy */

typedef struct element_t {
	void* data;
	struct element_t* prev;
	struct element_t* next;
} element_t;

typedef struct list_t {
    unsigned int size;
    unsigned int data_size;
    element_t* first;
    element_t* last;
} list_t;

element_t* elementAt(list_t* list, unsigned int pos) {
    element_t* e;
    unsigned int i;
    for (i = 0, e = list->first; e && i<pos; e = e->next, i++);
    return e;
}

element_t* createElement(void* data_loc, unsigned int data_size) {
    if (!data_loc) return NULL; 

    element_t* e = calloc(1, sizeof(element_t));
    if (e) {
        e->data = malloc(data_size);

        if (!e->data) {
            free(e);
            return NULL;
        }

        memcpy(e->data, data_loc, data_size);
    }
    return e;
}

list_t* createList(unsigned int data_size) {
    list_t* l = calloc(1, sizeof(list_t));
    if (l)
        l->data_size = data_size;
    return l;
}

bool insertFirst(list_t* list, void* data_loc) {
    element_t* e;
    if (!list) return false;
    if (!(e = createElement(data_loc, list->data_size))) return false; 

    e->next = list->first;

    if (e->next)
        e->next->prev = e;
    else
        list->last = e;

    list->first = e;

    list->size ++;
    return true;
}

bool insertLast(list_t* list, void* data_loc) {
    element_t* e;
    if (!list) return false;
    if (list->size == 0) return insertFirst(list, data_loc);
    if (!(e = createElement(data_loc, list->data_size))) return false; 

    e->prev = list->last;
    e->prev->next = e;
    list->last = e;

    list->size ++;
    return true;
}

bool insertAt(list_t* list, void* data_loc, unsigned int pos) {
    element_t *e, *aux;
    if (!list || pos > list->size) return false;
    if (pos == 0) return insertFirst(list, data_loc);
    if (pos == list->size) return insertLast(list, data_loc);

    if (!(e = createElement(data_loc, list->data_size))) return false; 
    if (!(aux = elementAt(list, pos-1))) return false;

    e->next = aux->next;
    e->prev = aux;

    aux->next->prev = e;
    aux->next = e;
    
    list->size ++;
    return true;
}

bool removeFirst(list_t* list, void** p_data_loc) {
    element_t* e;
    if (!list || !list->size) return false;

    e = list->first;
    *p_data_loc = e->data;
    list->first = e->next;
    free(e);

    if (list->first) 
        list->first->prev = NULL;

    if (list->size <= 2)
        list->last = list->first;

    list->size --;
    return true;
}

bool removeLast(list_t* list, void** p_data_loc) {
    element_t* e;
    if (!list || !list->size) return false;
    if (list->size == 1) return removeFirst (list, p_data_loc);

    e = list->last;
    *p_data_loc = e->data;
    list->last = e->prev;
    free(e);

    list->last->next = NULL;

    list->size --;
    return true;
}

bool removeAt(list_t* list, void** p_data_loc, unsigned int pos) {
    element_t *e;
    if (!list || pos >= list->size) return false;
    if (pos == 0) return removeFirst(list, p_data_loc);
    if (pos == list->size - 1) return removeLast(list, p_data_loc);

    if (!(e = elementAt(list, pos))) return false;

    e->next->prev = e->prev;
    e->prev->next = e->next;
    *p_data_loc = e->data;

    free(e);
    
    list->size --;
    return true;
}

bool removeAll(list_t* list) {
    element_t* aux;
    if (!list) return false;

    while (list->first) {
        aux = list->first;
        list->first = list->first->next;
        free(aux->data);
        free(aux);
    }

    list->last = NULL;
    list->size = 0;
    return true;
}

#define pBool(x) x ? 1 : 0
#define pEl(e) printf("%d - %d - %d\n", *(int*)e->data, pBool(e->prev), pBool(e->next))

void printList(list_t* list) {
    element_t* e;

    for (e = list->first; e; e = e->next)
        pEl(e);

    printf("Tamanho: %u\n\n", list->size);
}

void printBack(list_t* list) {
    element_t* e;

    for (e = list->last; e; e = e->prev)
        pEl(e);

    printf("Tamanho: %u\n\n", list->size);
}


int main() {
    int aux, r;
    void* vp;
    #define bindp(a, b) 0*(a=b) + &a

    /*crie a lista*/
    list_t* list = createList(sizeof(int));
    /*Leia a lista*/
    while((r = scanf("%d", &aux)) && r != EOF)
        insertLast(list, &aux); 

    /*Imprima a lista*/
    printList(list);

    /*Adicione um nó com o valor 43 no final da lista.*/
    insertLast(list, bindp(aux, 43));

    /*Adicione um nó com o valor 65 no final da lista.*/
    insertLast(list, bindp(aux, 65));

    /*Imprima a lista.*/
    printList(list);

    /*Adicione um nó com o valor 56 no início da lista.*/
    insertFirst(list, bindp(aux, 56));

    /*Adicione um nó com o valor 12 no início da lista.*/
    insertFirst(list, bindp(aux, 12));

    /* Imprima a lista.*/
    printList(list);

    /*Adicione um nó com o valor 10 na terceira posição da lista.*/
    insertAt(list, bindp(aux, 10), 2);

    /*Adicione um nó com o valor 15 na primeira posição da lista.*/
    insertAt(list, bindp(aux, 15), 0);

    /*Imprima a lista.*/
    printList(list);

    /*Remova os 3 últimos nós da lista.*/
    for (aux = 0; aux < 3; aux++){
        if (removeLast(list, &vp))
            free(vp);
    }

    /*Imprima a lista.*/
    printList(list);

    /*Remova os 3 primeiros nós da lista.*/    
    for (aux = 0; aux < 3; aux++){
        if (removeFirst(list, &vp))
            free(vp);
    }

    /*Imprima a lista.*/
    printList(list);

    /*Remova o nó que está na última posição da lista.*/
    if (removeLast(list, &vp))
        free(vp);

    /*Remova o nó que está na terceira posição da lista.*/
    if (removeAt(list, &vp, 2))
        free(vp);

    /*Imprima a lista.*/
    printList(list);

    /*Imprima a lista de trás para frente.*/
    printBack(list);

    /*Libere a lista.*/
    removeAll(list);
    free(list);

    return 0;
}

