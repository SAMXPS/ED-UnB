#include <stdio.h>
#include "../lifo_queue.c"

int main() {

    int aux, c, t;
    void* p;
    queue_t *queue = createQueue(sizeof(int));

    while (scanf("%d", &aux) && aux) {
        push(queue, &aux, 0);
    }
    t = c = 0;
    scanf("%d", &aux);

    while(pop(queue, &p)) {
        if (aux > 0) {
            if (*(int*)p == aux) {
                printf("Anilhas retiradas: %d\n", c);
                printf("Peso retirado: %d\n", t);
                aux = -1;
            } else {
                printf("Peso retirado: %d\n", *(int*)p);
                t+= *(int*)p;
                c++;
            }
        }
        free (p);
    }

    free(queue);
    return 0;
}