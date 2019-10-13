/* start includes*/
#include "../linked_list.c"
/*end includes */

/*implementação do backlista*/

typedef struct backList {
    int key;
    unsigned int time;
    element_t *back;
} _backList;

int backListcmp(data da, data db) {
    return ((_backList*)da)->key - ((_backList*)db)->key;
}

int main() {

    char opcode;
    int p;
    unsigned int time, pos;
    list_t* list = createTypeList(_backList);
    element_t** paux;
    element_t* eaux;
    _backList aux;
    data tst;
    time = 0;

    if (!list)
        return 0; /* Don't do anything, allocation falied... */

    while (scanf("%c", &opcode) && opcode != 'f') {
        if (opcode == 'i') {
            scanf("%d %d", &aux.key, &p);
            aux.time = time;
            aux.back = elementAt(list, list->size - p);
            insertLast(list, &aux);
        } else if (opcode == 'r') {
            scanf("%d", &aux.key);
            paux = findVal(list, &aux, &backListcmp, &pos);
            for (eaux = list->first; eaux; eaux = eaux->next){
                if (((_backList*)eaux->val)->back == *paux)
                    ((_backList*)eaux->val)->back = NULL;
            }
            removeAt(list, &tst, pos);
            free(tst);
        } else continue;
        time ++;
    }

    /* print the list */
    if (list->size) {
        for (eaux = list->first; eaux; eaux = eaux->next){
            aux = *((_backList*)eaux->val);
            printf("[%d,%u", aux.key, aux.time);
            if (aux.back && elementPos(list, aux.back, &pos)) {
                printf(",%u", pos);
            }
            printf("]");
        }
    } else {
        printf("-1");
    }
    printf("\n");
    return 0;
}