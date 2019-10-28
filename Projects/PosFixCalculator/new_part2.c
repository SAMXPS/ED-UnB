/*
    
    @author: Samuel James
    https://github.com/SAMXPS
    Universidade de Brasília, UnB
*/
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_LEN 201
typedef unsigned char byte;

typedef struct str_b {
    byte len;
    char buff[BUFFER_LEN];
} str_b;

typedef struct list_e {
    byte data;
    struct list_e* next;
} list_e;

void listAddFirst(list_e** list, byte data) {
    list_e* e = malloc(sizeof(list_e));
    e->next = *list;
    e->data = data;
    *list = e;
}

void listAddLast(list_e** list, byte data) {
    while (*list) list = &(*list)->next;
    return listAddFirst(list, data);
}

void listPush(list_e** list, byte data, int (*comp)(byte a, byte b)) {
    while (*list && comp(data, (*list)->data) >= 0) list = &(*list)->next;
    return listAddFirst(list, data);
}

bool listPop(list_e** list, unsigned int pos, byte* loc) {
    if (!*list) return false;
    list_e* e;
    if (pos == 0) {
        e = *list;
        *loc = e->data;
        *list = e->next;
        free(e);
        return true;
    } else return listPop(&(*list)->next, pos-1, loc);
}

void builderAppendCh(str_b* b, char c) {
    b->buff[b->len++] = c;
}

void builderAppendStr(str_b* b, char* str) {
    int s = strlen(str);
    memcpy(b->buff + b->len, str, s);
    b->len += s;
}

char* buildString(str_b* b) {
    char* str = malloc(b->len + 1);
    memcpy(str, b->buff, b->len);
    str[b->len] = 0;
    return str;
}

char ctx_open  [] = {'(', '[', '{'};
char ctx_close [] = {')', ']', '}'};
char operators [] = {'^', '*', '/', '+', '-'};
char precedence[] = { 1 ,  2 ,  2 ,  3 ,  3 };

bool _isPart(char c, char* l, int s) {
    int i;
    for (i=0; i<s; i++)
        if(l[i] == c) return true;
    return false;
}
#define isPart(a, b) _isPart(a, b, sizeof(b))

int idx(char c, char*l) {
    int i;
    for (i=0;; i++)
        if(l[i] == c) return i;
}

int prec(char op) {
    return precedence[idx(op, operators)];
}

bool isNumber(char c) {
    return c == '.' || ((c = (c - '0')) >= 0 && c < 10);
}

int contextLen(char* str) {
    int inside = 0, pos = 0;
    while(str[pos]) {
        if (isPart(str[pos], ctx_open)) inside++;
        else if (isPart(str[pos], ctx_close)) {
            if (!inside) {
                return pos-1;    
            }
            else inside--;
        }
        pos++;
    }
    return -1;
}

char* my_context;

int mycmp(byte a, byte b) {
    return prec(my_context[a]) - prec(my_context[b]);
}

char* convert(char* exp, int len);

void addNm(str_b*b, char* exp, list_e** nms) {
    byte d;
    char* proc;
    listPop(nms, 0, &d);
    printf("N%d", d);
    if (isPart(exp[d], ctx_open)) {
        proc = convert(exp + d + 1, contextLen(exp + d));
        builderAppendStr(b, proc);
        if (strlen(proc))
            builderAppendCh(b, ' ');
        free(proc);
        return;
    } else while (isNumber(exp[d])) {
        builderAppendCh(b, exp[d]);
        d++;
    }
    builderAppendCh(b, ' ');
}

void addOp(str_b*b, char* exp, list_e** ops) {
    byte d;
    listPop(ops, 0, &d);
    printf(".%d", d);
    builderAppendCh(b, exp[d]);
    builderAppendCh(b, ' ');
}

char* process(char* exp, list_e* ops, list_e* nms) {
    str_b sb = {0}; 
    while (ops) {
        while(nms && nms->data < ops->data) {
            addNm(&sb, exp, &nms);
        }
        if (nms) {
            addNm(&sb, exp, &nms);
        }
        addOp(&sb, exp, &ops);
    }
    return buildString(&sb);
}

char* convert(char* exp, int len) {
    int p = 0;
    #define curr exp[p]
    list_e* ops = NULL;
    list_e* nms = NULL;

    while(p<len) {
        if (curr == ' ') {
            p++;
            continue;
        }

        if (isPart(curr, operators)) {
            my_context = exp;
            listPush(&ops, (byte) p, &mycmp);
            p++;
            continue;
        }

        if (isPart(curr, ctx_open)) {
            listAddLast(&nms, (byte) p);
            p+= 2 + contextLen(exp + p);
            continue;
        }

        if (isNumber(curr)) {
            listAddLast(&nms, (byte) p);
            while(isNumber(curr)) p++;
            continue;
        }

        p++;
    }
    return process(exp, ops, nms);
}

void transforma(char* infixa, char* posfixa) {
    char* r = convert(infixa, strlen(infixa));
    strcpy(posfixa, r);
    free(r);
}

int main() {
    char infixa[101], posfixa[201];

    scanf("%100[^\n]", infixa);
    transforma(infixa, posfixa);
    printf("\n%s\n", posfixa);

    return 0;
}
