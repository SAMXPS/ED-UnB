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

#define NO_CONTEXT        '_'
#define OPERATION_CONTEXT ';'

#define CONTEXT         'C'
#define OPERAND         'R'
#define OPERATOR        '$'
#define OPERATION       '.'
#define NUMBER          '#'

/* Definição de Operador */
typedef char operator;

/* Definição de Operando */
typedef struct operand {
    char  type; /* CONTEXT or NUMBER or OPERATION or (temp) CONTEXT_BUILDER*/
    void* loc;
} operand;

typedef struct context_e {
    char  type; /* operand, operator*/
    void* data;
} context_e;

/* Definição de Operação */
typedef struct operation {
    operand  a;
    operand  b;
    operator op;
} operation;

typedef struct context {
    char type;
    operation operation;
} context;

typedef struct stack_e {
    struct stack_e* next;
    unsigned int data_len;
} stack_e;

typedef struct context_builder {
    char type;
    stack_e* context_stack;
} context_builder;

/* Implementação de stack genérica */

stack_e* createStackElement(void* data, unsigned int data_len) {
    stack_e* e = malloc(sizeof(stack_e) + data_len);
    if (e) {
        e->next = NULL;
        e->data_len = data_len;
        memcpy((e+sizeof(void*)), data, data_len);
    }
    return e;
}

bool stackPush(stack_e** stack, void* data, unsigned int data_len) {
    if (!stack) return false;
    stack_e* e = createStackElement(data, data_len);
    e->next = *stack;
    *stack = e;
    return true;
}

bool stackPop(stack_e** stack, stack_e** pop, void** data_loc) {
    if (!stack || !(*stack)) return false;
    *pop = *stack;
    *data_loc = *pop + sizeof(stack_e);
    *stack = (*stack)->next;
    return true;
}

/* fim da implementação de Stack */

unsigned char operator_precedence(char op) {
    if (op == OPERATOR_PLUS || op == OPERATOR_MINUS) {
        return 5;
    }
    if (op == OPERATOR_TIMES || op == OPERATOR_DIVIDE) {
        return 3;
    }
    if (op == OPERATOR_EXP) {
        return 1;
    }
    return 255;
}

context_e createOperatorE (char op_type) {
    context_e e;
    e.type = OPERATOR;
    e.data = malloc(sizeof(char));
    if (e.data) *(char*)(e.data) = op_type;
    return e;
}

context_e createOperandE (operand op) {
    context_e e;
    e.type = OPERAND;
    e.data = malloc(sizeof(operand));
    if (e.data) *(operand*)(e.data) = op;
    return e;
}

/* Create the operand and copies the data into it*/
operand createOperand(char type, void* data) {
    operand op;
    op.type = type;
    unsigned int len; 
    if (type == OPERATOR) {
        len = sizeof(operator);
    } else if (type == OPERATION) {
        len = sizeof(operation);
    } else if (type == NUMBER) {
        len = sizeof(double);
    } else if (type == OPERATION_CONTEXT) {
        len = sizeof(context_builder);
    }
    op.loc = malloc(len);
    if (op.loc) {
        memcpy(op.loc, data, len);
    }
    return op;   
}

context_builder* createContextBuilder(char type) {
    context_builder* cb = calloc(1, sizeof(context_builder));
    if (cb) {
        cb->type = type;
    }
    return cb;
}

bool contextBuilderForce(context_builder *cb, context_e* e) {
    if (!cb) return false;
    return stackForce(&cb->context_stack, e, sizeof(context_e));
}

bool contextBuilderPush(context_builder *cb, context_e* e) {
    if (!cb) return false;
    return stackPush(&cb->context_stack, e, sizeof(context_e));
}

bool contextBuilderPop(context_builder *cb, context_e* e) {
    context_e* data;
    stack_e* pop;
    if (!stackPop(&cb->context_stack, &pop, (void**) &data)) return false;
    *e = *data;
    free(pop);
    return true;
}

bool buildContext(context_builder *cb, context** ctx) {
    context *cx = malloc(sizeof(context));
    context* tmp;

    context_e aux;
    context_e last;
    context_e more;

    last.data = NULL;
    last.type = OPERATOR;

    operator lastOperator = 0;
    operator currOperator = 0;
    operand lastOperand, currOperand;

    operation myop;

    currOperand.type = 0;
    currOperand.loc = NULL;

    bool err = 1;

    if (cx) {
        err = 0;
        cx->type = cb->type;
        while (contextBuilderPop(cb, &aux) && !err) {
            if (last.type == OPERAND && aux.type == OPERATOR) {
                lastOperator = currOperator;
                currOperator = *(operator*)aux.data;
                if (lastOperator && currOperator) {
                    if (operator_precedence(currOperator) < operator_precedence(lastOperator)) {
                        context_builder* b = createContextBuilder(OPERATION_CONTEXT);

                        more = createOperatorE(lastOperator);
                        contextBuilderPush(b, &more);
                        more = createOperandE(lastOperand);
                        contextBuilderPush(b, &more);
                        more = createOperandE(currOperand);
                        contextBuilderPush(b, &more);

                        currOperand = createOperand(OPERATION_CONTEXT, b);
                        free(b);
                    } else {
                        mec:
                        if (lastOperand.type == OPERATION_CONTEXT) {
                            context_builder* b = (context_builder*) lastOperand.loc;
                            contextBuilderPop(b, &more);
                            lastOperand = * (operand*) more.data;
                            myop.a = currOperand;
                            myop.b = lastOperand;
                            myop.op = lastOperator;
                            more = createOperandE(createOperand(OPERATION, &myop));
                            contextBuilderForce(b, &more);

                            if (!buildContext(b, &tmp)) {
                                printf ("MASUE\n");
                                err =1;
                            } else {
                                myop = tmp->operation;
                                free (tmp);
                            }
                        } else {
                            myop.a = currOperand;
                            myop.b = lastOperand;
                            myop.op = lastOperator;
                            //lastOperand = NULL;
                        }
                        currOperand = createOperand(OPERATION, &myop);
                    }
                }
            } else if (last.type == OPERATOR && aux.type == OPERAND) {
                lastOperand = currOperand;
                currOperand = *(operand*)aux.data;
            } else err = 1;

            free(last.data);
            last = aux;
        }
        if (last.type != OPERAND) err = 1;
        free(last.data);
    }
    if (!err) {
        /* TODO: FIX REPEATED CODE */
        if (lastOperand.type == OPERATION_CONTEXT) {
            context_builder* b = (context_builder*) lastOperand.loc;
            contextBuilderPop(b, &more);
            lastOperand = * (operand*) more.data;
            myop.a = currOperand;
            myop.b = lastOperand;
            myop.op = lastOperator;
            more = createOperandE(createOperand(OPERATION, &myop));
            contextBuilderForce(b, &more);

            if (!buildContext(b, &tmp)) {
                printf ("MASUE\n");
                err =1;
            } else {
                myop = tmp->operation;
                free (tmp);
            }
        } else {
            myop.a = currOperand;
            myop.b = lastOperand;
            myop.op = lastOperator;
            //lastOperand = NULL;
        }
        cx->operation = myop;

        *ctx = cx;
        free(cb);
        return true;
    }

    /* TODO: clear the context*/
    free(cx);
    return false;
}


/* Para ordenar as operações conforme precedência de operador*/
/* < 0 : a first, == 0 equal, > 0 : b first*/
int cmp_operator_precedence(char* a, char* b) {
    return ((int) operator_precedence(*a) - (int) operator_precedence(*b));
}

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

void printContext(const context* ctx);
void printOperation(const operation op);

void printOperand(const operand op) {
    if (op.type == NUMBER) {
        printf("%.0lf", *(double*)op.loc);
        return;
    } 
    if (op.type == CONTEXT) {
        printContext((context*)op.loc);
        return;
    }
    if (op.type == OPERATION) {
        printOperation(*(operation*)op.loc);
        return;
    }
    printf("UNK");
}

void printOperation(const operation op) {
    printOperand(op.a);
    printf(" %c ", op.op);
    printOperand(op.b);
}

void printContext(const context* ctx) {
    printf("%c", ctx->type);
    printOperation(ctx->operation);
    printf("%c", ctx->type + (ctx->type == '(' ?  1 : 2));
}

bool validate(char* expr) {
    char* aux = expr;
    double num;
    char   op;
    context_e tmp;

    context_builder *cb = createContextBuilder(NO_CONTEXT);
    printf("%%b");
    while (*aux) {
        if (readNumber(aux, &aux, &num)) {
            printf("n");
            tmp = createOperandE(createOperand(NUMBER, &num));
            contextBuilderPush(cb, &tmp);
        } else {
            op = readNwChar(&aux);
            if (op) {
                printf("c");
                tmp = createOperatorE(op);
                contextBuilderPush(cb, &tmp);
            }
        }
    }

    context* x;
    if (buildContext(cb, &x)) {
        return true;
    }
    return false;
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