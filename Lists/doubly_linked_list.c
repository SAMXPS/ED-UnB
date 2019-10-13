/*
Lista Duplamente Encadeada - Implementação
@author: Samuel James
https://github.com/SAMXPS
Universidade de Brasília, UnB
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* for memcpy */

#include "doubly_linked_list.h"

element_t* elementAt(list_t* list, unsigned int pos) {
    element_t* e;
    unsigned int i;
    if (!list || pos > list->size-1) return NULL;

    if (pos <= list->size / 2){
        /* seeks forwards */
        for (i = 0, e = list->first; e && i<pos; e = e->next, i++);
    } else {
        /* seeks backwards */
        for (i = list->size-1, e = list->last; e && i>pos; e = e->prev, i--);
    }
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

bool freeList(list_t** list) {
    if (!list || !*list) return false;

    removeAll(*list);
    free(*list);
    *list = NULL;

    return true;
}

