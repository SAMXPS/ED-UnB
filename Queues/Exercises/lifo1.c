#include <stdio.h>

#include "../lifo_queue.c"

#define MAX_LEN 101

int mmpow(int a, unsigned int b) {
    if (b==0) return 1;
    if (b==1) return a;
    return a * mmpow(a, b-1);
}

bool parseInt(char* str, int* p) {
    int num = 0;
    bool neg = str[0] == '-';
    char tmp;
    if (neg) str = str+1;
    unsigned int i, len = strlen(str);
    for (i=0; i<len; i++){
        if (!((tmp = str[len-i-1] - '0') < 10)) return false;
        num += tmp * mmpow(10, i);
    }
    if (neg) num*=-1;
    *p = num;
    return true;
}

int main() {
    /* Variáveis auxiliares */
    int i;
    char aux[MAX_LEN];
    void* paux;

    /* Pilhas */
    queue_t* words   = createQueue(MAX_LEN * sizeof(char));
    queue_t* numbers = createQueue(sizeof(int));

    /* Leitura */
    while ((i=scanf("%s", aux)) && i != EOF && strcmp(aux, "end")) {
        if (parseInt(aux, &i))
            push(numbers, &i, 0);
        else
            push(words, aux, strlen(aux)+1);
    }

    /* Imprimir as stacks */
    printf("Palavras:\n");
    while (pop(words, &paux)) {
        printf("%s\n", paux);
        free(paux);
    }

    printf("Numeros:\n");
    while (pop(numbers, &paux)) {
        printf("%d\n", *(int*)paux);
        free(paux);
    }

    /* Liberar a memória */
    free(words);
    free(numbers);

    return 0;
}