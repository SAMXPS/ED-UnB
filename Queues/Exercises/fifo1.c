#include <stdio.h>

/*
    Fila - Header
    @author: Samuel James
    https://github.com/SAMXPS
    Universidade de Brasília, UnB
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef QUEUE_H
#define QUEUE_H

typedef struct element_t {
    char data;
    struct element_t* next;
} element_t;

typedef struct queue_t {
    unsigned int size;
    element_t* head;
    element_t* tail;
} queue_t;

element_t* createElement(char data);
queue_t*   createQueue();

bool  push(queue_t* queue, char data);
bool  pop(queue_t* queue, char* data_loc);
bool  isEmpty(queue_t* queue);
bool  removeAll(queue_t* queue);

char* head(queue_t* queue);

#endif /*QUEUE_H*/

element_t* createElement(char data) {

    element_t* e = calloc(1, sizeof(element_t));
    if (e)
        e->data = data;

    return e;
}

queue_t* createQueue() {
    return calloc(1, sizeof(queue_t));
}

bool removeAll(queue_t* queue) {
    char* ue;
    if (!queue) return false;
    while (pop(queue, ue));
    return true;
}

bool isEmpty(queue_t* queue) {
    return (!queue || !queue->size);
}

char* head(queue_t* queue) {
    if (queue && queue->head)
        return &(queue->head->data);
    return NULL;
}

/*
    Fila FIFO - Implementação
    @author: Samuel James
    https://github.com/SAMXPS
    Universidade de Brasília, UnB
*/

bool push(queue_t* queue, char data) {
    element_t* e;
    if (!queue) return false;
    if (!(e = createElement(data))) return false;

    if (queue->tail)
        queue->tail->next = e;
    else
        queue->head = e;

    queue->tail = e;

    queue->size ++;
    return true;
}

bool pop(queue_t* queue, char* data_loc) {
    element_t* e;
    if (!queue || !queue->head) return false;

    e = queue->head;
    *data_loc = e->data;
    queue->head = e->next;

    if (!queue->head || !queue->head->next)
        queue->tail = queue->head;

    free(e);

    queue->size --;
    return true;
}

int countPalin(char* str) {
    queue_t *charb = createQueue();
    int i;
    for (i=0;i<strlen(str);i++) {
        faaaaaaz isso aquioo
    }
}

int main() {
    char buffer[1024];
    int i;

    while ((i = scanf("%s", buffer)) && i!= EOF) {
        if (countPalin(buffer)>1) {
            printf("%s\n", buffer);
        }
    }

    return 0;
}