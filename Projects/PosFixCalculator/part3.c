/*
    Calculadora (simples) Pos-fixa
    @author: Samuel James
    https://github.com/SAMXPS
    Universidade de Brasília, UnB
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Implementation of Stack */

/* stack of double-floating point operands */
typedef struct op_stack_e {
    double op;
    struct op_stack_e* next;
} op_stack_e; 

typedef struct op_stack {
    op_stack_e* head;
} op_stack;

op_stack_e* createElement(double op) {
    op_stack_e* e = malloc(sizeof(op_stack_e));
    if (e) {
        e->op = op;
        e->next = NULL;
    }
    return e;
}

op_stack* createStack() {
    op_stack* stack = malloc(sizeof(op_stack));
    if (stack) {
        stack->head = NULL;
    }
    return stack;
}

bool pushStack(op_stack* stack, double op) {
    op_stack_e* e;
    if (!stack) return false;
    if (!(e = createElement(op))) return false;

    e->next = stack->head;
    stack->head = e;

    return true;
}

bool pullStack(op_stack* stack, double* p_op) {
    op_stack_e* e;
    if (!stack || !stack->head) return false;

    e = stack->head;
    stack->head = e->next;
    *p_op = e->op;
    free(e);

    return true;
}

/* End of Stack implementation */

/* Start of calculator */

bool operate(op_stack* stack, char operator) {
    double a, b;
    if (!pullStack(stack, &b)) return false;
    if (!pullStack(stack, &a)) {
        pushStack(stack, b);
        return false;
    }

    switch (operator) {
        case '+':
            a += b;
            break;
        case '-':
            a -= b;
            break;
        case '*':
            a *= b;
            break;
        case '/':
            a /= b;
            break;
        case '^':
            a = pow(a, b);
            break;
        default:
            pushStack(stack, a);
            pushStack(stack, b);
            return false;
    }
    pushStack(stack, a);

    return true;
}

int readOperand(char* str, char** up, double* loc) {
    char* diff = str;
    *loc = strtod(str, &diff);
    if (up) *up = diff;
    return diff-str;
}

char readOperator(char** str) {
    while(**str == ' ' && (*str)++);
    return **str;
}

double calculate(char* const posfix) {
    char* aux = posfix;
    const int len = strlen(posfix);
    double v = 0;

    op_stack* stack = createStack();

    while (aux-posfix <= len) {
        if (readOperand(aux, &aux, &v)){
            pushStack(stack, v);
        } else {
            operate(stack, readOperator(&aux));
            aux++;
        }
    }

    while (pullStack(stack, &v));
    free(stack);
    return v;
}

int main() {
    char posfix[201];

    scanf("%200[^\n]", posfix);
    printf("%.5lf\n", calculate(posfix));

    return 0;
}
