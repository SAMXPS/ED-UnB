/*
Lista Encadeada Simples - Header
@author: Samuel James
https://github.com/SAMXPS
Universidade de Brasília, UnB
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#define createTypeList(type) createList(sizeof(type))

typedef void* data;

typedef struct element_t {
    data val;
    struct element_t* next;
} element_t;

typedef struct list_t{
    unsigned int size;
    unsigned int type_len;
    element_t *first;
    element_t *last;
} list_t ;

element_t*  createElement(data val, unsigned int data_len);
element_t*  elementAt(list_t* const list, const unsigned int pos);
list_t*     createList(unsigned int type_len);



bool isEmpty(list_t* const list);

bool insertFirst(list_t* const list, const data val);
bool insertLast(list_t* const list, const data val);
bool insertAt(list_t* const list, const data val, const unsigned int pos);

bool removeFirst(list_t* const list, data* val);
bool removeLast(list_t* const list, data* val);
bool removeAt(list_t* const list, data* val, const unsigned int pos);

void removeAll(list_t* const list);
void freeList(list_t** list);
void printList(list_t* const list);

unsigned int removeVal(list_t* const list, const data val, int (*datacmp)(data a, data b));
unsigned int countVal(list_t* const list, const data val, int (*datacmp)(data a, data b));
element_t**  findVal(list_t* const list, const data val, int (*datacmp)(data a, data b), unsigned int *pos);

/* datacmp(data a, data b) should return 0 when the two data are equal,
  * positive if a > b,
  * negative if a < b
*/

#endif /*LINKED_LIST_H*/