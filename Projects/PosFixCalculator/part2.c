/*    
    @author: Samuel James
    https://github.com/SAMXPS
    Universidade de Brasília, UnB
*/
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef DEBUG
#define dprint(...) printf(__VA_ARGS__)
#else
#define dprint(...) 
#endif

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

bool listPop(list_e** list, unsigned int pos, byte* loc) {
    if (!*list) return false;
    list_e* e;
    if (pos == 0) {
        e = *list;
        if (loc)
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
    int inside = 0, pos = 1;
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
    int d = prec(my_context[a]) - prec(my_context[b]);
    if (!d && prec(my_context[a]) == 1) {
        return b - a;
    }
    return d;
}

char* convert(char* exp, int len);

void addNm(str_b*b, char* exp, list_e** nms) {
    byte d;
    char* proc;
    listPop(nms, 0, &d);
    dprint("N%d", d);
    if (isPart(exp[d], ctx_open)) {
        dprint("Exploding context at %d [len=%d]\n", d, contextLen(exp + d));
        proc = convert(exp + d + 1, contextLen(exp + d));
        dprint("Context %d result: %s\n", d, proc);
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
    dprint(".%d", d);
    builderAppendCh(b, exp[d]);
    builderAppendCh(b, ' ');
}

int feedUpTo(str_b* sb, char* exp, list_e** nms, byte p) {
    int n = 0;
    while (*nms && (*nms)->data < p) {
        addNm(sb, exp, nms);
        n++;
    }           
    return n;
}

char* process(char* exp, list_e* ops, list_e* nms) {
    str_b sb = {0};
    list_e* wait = NULL;
    unsigned char o_c = 0, n_c = 0;
    if (!ops && nms) {
        addNm(&sb, exp, &nms);
        n_c++;
    } else while (ops || wait) {
        my_context = exp;
        if (wait && (!ops || mycmp(wait->data, ops->data) <= 0)) {
            n_c += feedUpTo(&sb, exp, &nms, wait->data);
            addOp(&sb, exp, &wait);
        } else if (ops && ops->next && mycmp(ops->data, ops->next->data) > 0){
            listAddFirst(&wait, ops->data);
            listPop(&ops, 0, NULL);
        } else {
            o_c++;
            n_c += 1 + feedUpTo(&sb, exp, &nms, ops->data);
            addNm(&sb, exp, &nms); 
            addOp(&sb, exp, &ops);
        }
    }

    if (sb.len && sb.buff[sb.len-1] == ' ')
        sb.len--;
    return buildString(&sb);
}

char* convert(char* exp, int len) {
    int p = 0, i;
    #define curr exp[p]
    list_e* ops = NULL;
    list_e* nms = NULL;

    while(p<len) {
        if (curr == ' ') {
            p++;
            continue;
        }

        if (isPart(curr, operators)) {
            listAddLast(&ops, (byte) p);
            dprint("Operator at %d\n", p);
            p++;
            continue;
        }

        if (isPart(curr, ctx_open)) {
            listAddLast(&nms, (byte) p);
            i = contextLen(exp + p);
            dprint("Context found at %d [len=%d]\n", p, i);
            p += 2 + i;
            continue;
        }

        if (isNumber(curr)) {
            listAddLast(&nms, (byte) p);
            dprint("Number found at %d\n", p);
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
    dprint("\n");
}

int main() {
    char infixa[101], posfixa[201];

    scanf("%100[^\n]", infixa);
    transforma(infixa, posfixa);
    printf("%s\n", posfixa);

    return 0;
}
