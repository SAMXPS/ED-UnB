#include <stdio.h>
#include <assert.h>
#include "linked_list.h"

int datacmp(data da, data db) {
    return *(int*)da - *(int*)db;
}

/*only works for integer data type*/
void printList(list_t* const list) {
    element_t *aux = list->first;
    printf("List[%d] : {", list->size);
    if (list->size) {
        while (aux) {
            printf(" %d,", *(int*)(aux->val));
            aux = aux->next;
        }
        printf("\b }\n");
    } else {
        printf(" }\n");
    }
}

int main() {
    list_t* list = createTypeList(int);
    int v, i;
    unsigned int p;

    assert(list);

    for (i=0; i<10; i++)
        insertFirst(list, &i);

    printList(list);

    removeAll(list);
    printList(list);

    assert(isEmpty(list));

    for (i=0; i<10; i++)
        insertLast(list, &i);

    printList(list);

}