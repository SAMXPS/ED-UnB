/*
    
    @author: Samuel James
    https://github.com/SAMXPS
    Universidade de Brasília, UnB
*/
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char ctx_open [] = {'(', '[', '{'};
char ctx_close[] = {')', ']', '}'};
char operators[] = {'+', '-', '*', '/', '^'};

#define isPart(a, b) _isPart(a, b, sizeof(b))
bool _isPart(char c, char* l, int s) {
    int i;
    for (i=0; i<s; i++)
        if(l[i] == c) return true;
    return false;
}

int idx(char c, char*l) {
    int i;
    for (i=0;; i++)
        if(l[i] == c) return i;
}

bool isNumber(char c) {
    return (c = (c - '0')) >= 0 && c < 10;
}


bool validate(const char* exp, int len) {
    int p = 0, i;
    bool type = 0; 
    /* 
    1 - operando
    0 - operador
    */

    while (p<len) {
        #define curr exp[p]

        if (curr == ' ') {
            p++;
            continue;
        }
        if (!type) {
            if (isNumber(curr)) {
                while(p<len && isNumber(curr)) {
                    p++;
                }
                type = 1;
                continue;
            }
            else if (isPart(curr, ctx_open)) {
                i = p;
                while (1) {
                    if (p == len) {
                        return false;
                    }
                    if (isPart(curr, ctx_close)) {
                        if (idx(curr, ctx_close) != idx(exp[i], ctx_open)) {
                            /* Wrong context close */
                            return false;
                        }
                        i++;
                        if (!validate(exp + i, p-i)) return false;
                        break;
                    }
                    p++;
                }
                type = 1;
            } else return false;
        } else if (isPart(curr, operators)) {
            type = 0;
            p++;
            continue;
        } else return false;
        p++;
    }
    return type;
}

bool valida(const char* expressao) {
    return validate(expressao, strlen(expressao));
}

int main() {
    char expressao[101];
    
    scanf("%100[^\n]", expressao);
    
    if (valida(expressao))
        printf("VALIDA\n");
    else
        printf("INVALIDA\n");
        
    return 0;
}

