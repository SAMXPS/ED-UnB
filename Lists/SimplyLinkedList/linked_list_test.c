#include <stdio.h>
#include <assert.h>
#include "linked_list.h"

int main() {
    list_t* list = createList();
    int v;
    unsigned int p;

    assert(list);

    for (int i=0; i<10; i++)
        insertFirst(list, i);

    printList(list);
    removeAll(list);
    printList(list);

    assert(isEmpty(list));

    for (int i=0; i<10; i++)
        insertLast(list, i);

    printList(list);

    insertAt(list, 77, 10);

    printList(list);


    findVal(list, 77, &p);
    printf("77 At: %u\n", p);
    removeVal(list, 77);


    printList(list);
    removeFirst(list, &v);
    printf("pop: %d\n", v);
    printList(list);


}