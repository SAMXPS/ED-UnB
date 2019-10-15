#include <stdio.h>
#include "../lifo_queue.c"


#define MAX_LEN 51

typedef struct {
    char name [MAX_LEN];
    char color[MAX_LEN];
    unsigned int cost;
} cloth;

void printCloth(cloth* c) {
    if (c) printf("Tipo: %s Cor: %s\n", c->name, c->color);
}

int main() {

    int i, t;
    cloth c;
    cloth* p;

    queue_t* queue = createQueue(sizeof(cloth));

    while ((i = scanf("%s", c.name)) && i != EOF && strcmp(c.name, "end")) {
        scanf("%s %u", c.color, &c.cost);
        push(queue, &c, 0);
    }
    t = i = 0;

    while (pop(queue, (void**) &p)) {
        t+=p->cost;
        printCloth(p);
        free(p);
        i++;
    }

    printf("Total de roupas = %d\n", i);
    printf("Total de tempo = %d\n", t);

    free(queue);

    return 0;
}