#include <stdio.h>

#include "../fifo_queue.c"

#define MAX_LEN 50

int main() {

    int i, N;
    queue_t* ql[10];
    char str[MAX_LEN];
    char c;
    void *aux;

    for (i=0;i<10;i++) {
        ql[i] = createQueue(MAX_LEN);
    }

    while (scanf("%s %d", str, &i)) {
        push(ql[i], str, strlen(str)+1);
        if (!scanf("%c",&c) || c=='\n')
            break;
    }

    for (scanf("%d", &N), i = 0; N>0; N--) {
        for(;i<10;i++) {
            if (pop(ql[i], &aux)) {
                free (aux);
                break;
            }
        }
    }

    for (N=0, i=0;i<10;i++) {
        N+= ql[i]->size;
    }

    printf("Tamanho da fila: %d\n", N);

    for (i=0;i<10;i++) {
        while (pop(ql[i], &aux)){
            printf("Atividade: %s Prioridade: #%d\n", (char*)aux, i);
            free(aux);
        }
        free(ql[i]);
    }

    return 0;
}