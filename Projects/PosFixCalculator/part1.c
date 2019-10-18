/*
    
    @author: Samuel James
    https://github.com/SAMXPS
    Universidade de Brasília, UnB
*/
#define DEBUG true

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Definições de caracteres para facilitar o entendimento do código*/

#define CONTEXT_A       '('
#define CONTEXT_A_CLOSE ')'
#define CONTEXT_B       '['
#define CONTEXT_B_CLOSE ']'
#define CONTEXT_C       '{'
#define CONTEXT_C_CLOSE '}'
#define OPERATOR_PLUS   '+'
#define OPERATOR_MINUS  '-'
#define OPERATOR_TIMES  '*'
#define OPERATOR_DIVIDE '/'
#define OPERATOR_EXP    '^'

#define NO_CONTEXT      '_'
#define OPERAND         'R'
#define OPERATOR        '$'
#define ANY_OPERATION   '@'
#define CNTX_OR_OPRND   '!'  

/* Definição de Operando */
typedef struct operand {
    bool  ctx;
    void* loc;
} operand;

/* Definição de Operação */
typedef struct operation {
    operand a;
    operand b;
    char   operator;
} operation;

/* Fila FIFO de operações */
typedef struct operation_queue_e {
    operation data;
    struct operation_queue_e* next;
} operation_queue_e;

typedef struct operation_queue_t {
    operation_queue_e* head;
} operation_queue_t;

/* Definição de Contexto */
typedef struct context {
    char type;
    operation_queue_t operation_queue;
} context;


bool isContextOpen(char code) {
    return code == CONTEXT_A || 
           code == CONTEXT_B ||
           code == CONTEXT_C;
}

bool isContextClose(char code) {
    return code == CONTEXT_A_CLOSE ||
           code == CONTEXT_B_CLOSE ||
           code == CONTEXT_C_CLOSE;
}

/* Função que lê um número real a partir da string */
int readNumber(char* str, char** up, double* loc) {
    char* diff = str;
    *loc = strtod(str, &diff);
    if (up) *up = diff;
    return diff-str;
}

/* Read non-white character */
char readNwChar(char** str) {
    while(**str == ' ' && (*str)++);
    return **str;
}

bool validate(char* const expr) {
    char* aux = expr;
    char* err = NULL;
    const int len = strlen(expr);
    double val;
    char   opr;
    bool   ret = true;
    
    // TODO: O código abaixo ainda está incompleto
    stack_e  aux_e;
    stack_t* stack = createStack();

    while (aux-expr <= len) {
        if (stack->expect == CNTX_OR_OPRND || stack->expect == ANY_OPERATION) {
            if (readOperand(aux, &aux, &val)) {
                pushStack(stack, OPERAND, val);
                stack->expect = OPERATOR;
            } else {
                opr = readOperator(&aux);

                if (isContextClose(opr)) {
                    if (stack->context == NO_CONTEXT) {
                        err = "Unexpected context close";
                        goto error;
                    } else {
                        pushStack(stack, opr, opr);

                        stack->expect = OPERATOR OR CONTEXT_CLOSE;
                    }
                } else {
                    
                }

                stack->expect = CNTX_OR_OPRND;
            }
        }
        if (stack->expect == OPERAND) {
            if (!readOperand(aux, &aux, &val)) goto error;
            pushStack(stack, OPERAND, val);
            stack->expect = OPERATOR;
        }
        if (stack->expect == OPERATOR) {
            if (readOperand(aux, &aux, &val)) goto error;
            opr = readOperator(&aux);
            stack->expect = CNTX_OR_OPRND;
        }
    }

    goto end;

    /* Simple expression error handling */
    error: {
        if (DEBUG && err) printf("%s\n", err);
        ret = false;
    }

    end:
    while (pullStack(stack, &aux_e));
    free(stack);
    return ret;
}

/* Função main dada pelo problema */
int main() {
    char expr[101];
    
    scanf("%100[^\n]", expr);
    
    if (validate(expr))
        printf("VALIDA\n");
    else
        printf("INVALIDA\n");
        
    return 0;
}