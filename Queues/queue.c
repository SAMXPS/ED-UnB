#include <stdlib.h>
#include <string.h>
#include "queue.h"

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

queue_t* createQueue(unsigned int data_size) {
    queue_t* queue = calloc(1, sizeof(queue_t));

    if (queue)
        queue->data_size = data_size;

    return queue;
}

bool removeAll(queue_t* queue) {
    void* aux;
    if (!queue) return false;

    while (pop(queue, &aux))
        free(aux);

    return true;
}

bool isEmpty(queue_t* queue) {
    return (!queue || !queue->size);
}

void* head(queue_t* queue) {
    if (queue && queue->head)
        return queue->head->data;
    return NULL;
}
