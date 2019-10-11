#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#define DATA_TYPE int
typedef DATA_TYPE data;

typedef struct element_t {
    data val;
    struct element_t* next;
} element_t;

typedef struct list_t{
    int size;
    element_t *first;
    element_t *last;
} list_t ;

element_t*  createElement(data val);
element_t*  elementAt(list_t* const list, const unsigned int pos);
element_t** findVal(list_t* const list, const data val, unsigned int *pos);
list_t*     createList();

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

unsigned int removeVal(list_t* const list, const data val);
unsigned int countVal(list_t* const list, const data val);


#endif //LINKED_LIST_H