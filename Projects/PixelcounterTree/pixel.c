#include <stdio.h>
/*#include <math.h>*/

#define PARENT 'p'
#define WHITE  'e'
#define BLACK  'f'
#define tpow(b) (1<<(b))

void jump(char**parent) {
    int i;
    if (*((*parent)++) == PARENT) {
        for (i=0;i<4;i++) {
           jump(parent);
        }
    }
}

int cv(char**parent, int level) {
    int s = 0, i;
    char c = **parent;
    (*parent)++;
    if (c == BLACK) {
        s = tpow(10-2*level);
    } else if (c == PARENT) {
        for (i=0;i<4;i++) {
           s+=cv(parent, level+1);
        }
    }
    return s;
}

int count(char**p1, char**p2, int level) {
    int i;
    int sum = 0;
    char aux1, aux2;
    aux1 = **p1;
    aux2 = **p2;
    if (aux1 == BLACK || aux2 == BLACK){
        sum+=tpow(10-2*level);
        jump(p1);
        jump(p2);
    } else if (aux1 == PARENT || aux2 == PARENT) {
        if (aux1 == aux2) {
            (*p1)++;
            (*p2)++;
            for (i=0;i<4;i++) {
                sum+= count(p1, p2, level+1);
            }
        } else if (aux1 == PARENT) {
            sum+=cv(p1, level);
            (*p2)++;
        } else {
            sum+=cv(p2, level);
            (*p1)++;
        }
    } else {
        (*p1)++;
        (*p2)++;
    }

    return sum;
}

int main() {
    char ba[2044];
    char bb[2044];
    scanf("%[^\n] %[^\n]", ba, bb);
    char*a = ba; char*b = bb;

    printf("%d", count(&a, &b, 0));
    return 1;
}