/*
    Fila LIFO (Stack) - Implementação
    @author: Samuel James
    https://github.com/SAMXPS
    Universidade de Brasília, UnB
*/
#include "queue.c"

bool push(queue_t* queue, void* data_loc, unsigned int data_size) {
    element_t* e;
    if (!queue) return false;
    if (!data_size) data_size = queue->data_size;
    if (!(e = createElement(data_loc, data_size))) return false;

    e->next = queue->head;
    queue->head = e;

    queue->size ++;
    return true;
}

bool pop(queue_t* queue, void** p_data_loc) {
    element_t* e;
    if (!queue || !queue->head) return false;

    e = queue->head;
    *p_data_loc = e->data;
    queue->head = e->next;

    free(e);

    queue->size --;
    return true;
}
