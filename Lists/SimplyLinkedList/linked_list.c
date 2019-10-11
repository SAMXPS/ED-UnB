#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

element_t* createElement(data val) {
    element_t* el = calloc(1, sizeof(element_t));
    if (el)
        el->val = val;
    return el;
}

element_t* elementAt(list_t* const list, const unsigned int pos) {
    element_t * e = list->first;
    for (int i=0; e && i<pos; i++)
        e = e->next;
    return e;
}

element_t** findVal(list_t* const list, const data val, unsigned int *pos) {
    element_t ** e = &(list->first);
    for (*pos=0; *e; (*pos)++) {
        if ((*e)->val == val)
            return e;
        e = &((*e)->next);
    }
    return NULL;
}

list_t* createList() {
    return calloc(1, sizeof(list_t));
}

bool isEmpty(list_t *const list) {
    return list->size == 0 && !list->first && !list->last;
}

bool insertFirst(list_t* const list, const data val) {
    element_t* e = createElement(val);
	if (!e)
        return false;

    e->next = list->first;

    if (!list->last)
        list->last = e;

    list->first = e;
    list->size++;
    return true;
}

bool insertLast(list_t* const list, const data val){
	element_t* e = createElement(val);
	if (!e)
        return false;

    if (list->last)
        list->last->next = e;
    else
        list->first = e;

    list->last = e;
    list->size++;
    return true;
}

bool insertAt(list_t* const list, const data val, const unsigned int pos){
    if (pos == 0)
        return insertFirst(list, val);
    else if (pos == list->size)
        return insertLast(list, val);
    else if (pos > list->size)
        return false;

	element_t* e = createElement(val);
	if (!e)
        return false;

    element_t* prev = elementAt(list, pos-1);
    e->next = prev->next;
    prev->next = e;

    list->size++;
    return true;
}

bool removeFirst(list_t* const list, data* val){
    if (!list->first)
        return false;

    element_t *aux = list->first->next;
    *val = list->first->val;
    free(list->first);

    list->first = aux;

    if (!aux || !aux->next)
        list->last = aux;

    list->size--;
    return true;
}

bool removeLast(list_t* const list, data* val){
    if (!list->last)
	    return false;

    if (list->size == 1)
        return removeFirst(list, val);

    *val = list->last->val;
    free(list->last);

    list->last = elementAt(list, list->size-2);
    list->last->next = NULL;

    list->size --;
    return true;
}

bool removeAt(list_t* const list, data* val, const unsigned int pos){
    if (pos == 0)
        return removeFirst(list, val);

    if (pos == list->size-1)
        return removeLast(list, val);

    if (pos > list->size-1)
        return false;

    element_t *prev = elementAt(list, pos - 1);
    element_t *aux;

    if (!prev || !prev->next)
        return false;

    aux = prev->next;
    *val = aux->val;
    prev->next = aux->next;

    free(aux);

    list->size --;
    return true;
}

void removeAll(list_t* const list) {
    element_t *aux;

    while ((aux = list->first) != NULL) {
        list->first = aux->next;
        free(aux);
    }

    list->last = NULL;
    list->size = 0;
}

void freeList(list_t** list) {
    if(list && *list){
        removeAll(*list);
        free(*list);
    }
    *list = NULL;
}

void printList(list_t* const list) {
    element_t *aux = list->first;
    printf("List[%d] : {", list->size);
    if (list->size) {
        while (aux) {
            printf(" %d,", aux->val);
            aux = aux->next;
        }
        printf("\b }\n");
    } else {
        printf(" }\n");
    }
}

unsigned int removeVal(list_t* const list, const data val) {
    int count = 0;

    element_t* aux = list->first;
    element_t* last_valid = NULL;
    element_t **p_aux = &(list->first);

    while(aux) {
        if (aux->val == val) {
            *p_aux = aux->next;
            free(aux);
            aux = *p_aux;
            count++;
        } else {
            last_valid = aux;
            p_aux = &(aux->next);
            aux = aux->next;
        }
    }

    list->last = last_valid;
    list->size -= count;

    return count;
}

unsigned int countVal(list_t* const list, const data val){
    int count = 0;
    element_t *aux;
    aux = list->first;
    while (aux) {
        if (aux->val == val)
            count++;
        aux = aux->next;
    }
    return count;
}
/*

int remove_val(list_t *list, data val) {
    int count = 0;

    element_t** aux, *bux, *cux = NULL;
    aux = &(list->first);

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

    list->last = cux;
    list->size -= count;

    return count;
}


int change_first(list_t* const const b, data v1, data v2) {
    int c = 0;
    element_t *aux;
    aux = list->first;
    while (aux) {
        if (aux->val == v1) {
            aux->val = v2;
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}*/