/*
Lista Duplamente Encadeada - Implementação
@author: Samuel James
https://github.com/SAMXPS
Universidade de Brasília, UnB
*/

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include <stdbool.h>

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

element_t*  elementAt(list_t* list, unsigned int pos);
element_t*  createElement(void* data_loc, unsigned int data_size);
list_t*     createList(unsigned int data_size);

bool insertFirst(list_t* list, void* data_loc);
bool insertLast(list_t* list, void* data_loc);
bool insertAt(list_t* list, void* data_loc, unsigned int pos);

bool removeFirst(list_t* list, void** p_data_loc);
bool removeLast(list_t* list, void** p_data_loc);
bool removeAt(list_t* list, void** p_data_loc, unsigned int pos);
bool removeElement(list_t* list, element_t* e);

bool removeAll(list_t* list);
bool freeList(list_t** list);

#endif /*DOUBLY_LINKED_LIST_H*/