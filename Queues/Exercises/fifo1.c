#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    char* l;
    int v;
    int h_len;
    int v_len;
} strList;

char* getLaddr(strList*sl, int l) {
    return (sl->l + l*(sl->h_len+1));
}

strList* createStrList(int h_len, int v_len) {
    /*printf("Creating STRLIST  %dx%d\n", h_len, v_len);*/
    strList* sl = malloc(sizeof(strList));
    int i;
    if (sl) {
        sl->l = malloc((h_len+1) * v_len);
        if (!sl->l) {
            free(sl);
            sl=NULL;
        } else {
            sl->h_len = h_len;
            sl->v_len = v_len;
            sl->v = 0;
            for (i=1; i<=v_len;i++)
                *(getLaddr(sl, i)-1) = 0;
        }
    }
    return sl;
}

void mmprint(char* str, int len) {
    int i;
    for (i=0;i<len;i++){
        putchar(str[i]);
    }
}

#define mymin(a,b) (((a) < (b)) ? (a) : (b))

void addStrList(strList*sl, char* str, int len) {
    char* aux = getLaddr(sl, sl->v);
    int l = mymin(len, sl->h_len);
    memcpy(aux, str, l);
    aux[l] = 0;
    /*printf("added: %s\n", aux);*/
    sl->v++;
}

/* assuming  la<=lb*/
bool hasStrPart(char*stra, int la, char*strb, int lb) {
    int i;
    /*mmprint(stra, la);
    printf(" is inside ");
    mmprint(strb, lb);
    printf("? ");*/
    for (i=0;i<=lb-la;i++) {
        if (!strncmp(stra, strb+i, la)){
           /* printf("yes\n");*/
            return true;
        }
    }
   /* printf("no\n");*/
    return false;
}

bool hasPart(strList*sl, char*str, int len) {
    int i;
    for (i=0;i<sl->v;i++){
        char* str2 = getLaddr(sl, i);
        int len2 = strlen(str2);
        if (hasStrPart(str2, len2, str, len))
            return true;
    }
    return false;
}


bool isPalin(char* str, int len) {
    int i;
    for (i=0;i<len;i++){
        if (str[i] != str[len-1-i])
            return false;
    }
    return true;
}

bool is2palin(char* str) {
    int size = strlen(str);
    strList* list = createStrList(size,size);
    int i, n;
    if (size > 3) {
        for (n=3; n<size; n++) {
            for (i=0; i<(size-n)+1;i++){
                if (isPalin(str+i,n)) {
                    if (!hasPart(list, str+i, n)) {
                        addStrList(list, str+i, n);
                    }
                }
            }
        }
    }
    /*printf("%s: (%d) [", str, list->v);
    
    for (i=0;i<list->v;i++){
        printf("%s, ", getLaddr(list, i));
    }
    
    printf("]\n");*/

    n = list->v;
    free(list->l);
    free(list);
    return n >= 2;
}

void tst(char* str) {
    int i;
    if (isPalin(str, strlen(str))) {
        for (i=0;i<strlen(str);i++){
            putchar(str[i]);
        }
        printf(" is palin\n");
    }
}

int main() {

    char buffer[512];
    int i;

    while ((i = scanf("%s", buffer)) && i != EOF) {
        if (is2palin(buffer)) {
            printf("%s\n", buffer);
        }
    }

    return 0;
}