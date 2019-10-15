/*
    Fila - Header
    @author: Samuel James
    https://github.com/SAMXPS
    Universidade de Brasília, UnB
*/

#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>

typedef struct element_t {
    void* data;
    struct element_t* next;
} element_t;

typedef struct queue_t {
    unsigned int size;
    unsigned int data_size;
    element_t* head;
    element_t* tail;
} queue_t;

element_t* createElement(void* data_loc, unsigned int data_size);
queue_t*   createQueue(unsigned int data_size);

bool  push(queue_t* queue, void* data_loc, unsigned int data_size);
bool  pop(queue_t* queue, void** p_data_loc);
bool  isEmpty(queue_t* queue);
bool  removeAll(queue_t* queue);

void* head(queue_t* queue);

#endif /*QUEUE_H*/