#include <stdio.h>
#include <assert.h>
#include "doubly_linked_list.h"

void printList(list_t* list) {
    element_t* e;

    printf("DLL[%u] : {", list->size);

    if (list->size) {
        for (e = list->first; e; e = e->next)
            printf("%d, ", *(int*)(e->data));
    } else printf("  ");

    printf("\b\b}\n");
}

#define bindPointer(a, b) 0*(a=b) + &a

int main() {
    element_t* aux;
    list_t* list = createList(sizeof(int));
    int i, v, *int_p;

    for(i=0;i<10;i++) {
        insertLast(list, &i);
    }

    insertAt(list, bindPointer(v, 5), 10);
    assert(!insertAt(list, &v, 12));

    printList(list);

    for(i=0; i<10; i++) {
        aux = elementAt(list, i);
        assert(aux);
        assert(*(int*)(aux->data) == i);
    }

    aux = elementAt(list, 10);
    assert(aux);
    assert(*(int*)(aux->data) == 5);

    removeAt(list, (void**)&int_p, 2);
    assert(*int_p == 2);
    printList(list);

    removeAt(list, (void**)&int_p, 9);
    assert(*int_p == 5);
    printList(list);

    return 0;
}