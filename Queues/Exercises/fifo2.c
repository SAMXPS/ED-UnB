#include <stdio.h>

#include "../fifo_queue.c"

#define MAX_LEN 50

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

    char str[MAX_LEN];
    int N = -1;
    char* aux;
    queue_t *queue = createQueue(MAX_LEN*sizeof(char));

    while (scanf("%s", str) && !parseInt(str, &N)) {
        push(queue, str, strlen(str)+1);
    }

    if (!isEmpty(queue)) {
        for(;N>0;N--){
            pop(queue, (void**) &aux);
            push(queue, aux, strlen(aux) + 1);
        }
        printf("Pessoa da frente: %s\n", (char*) head(queue));
        printf("Pessoa do fim: %s\n", (char*)(queue->tail->data));
    }

    removeAll(queue);
    free(queue);

    return 0;

}