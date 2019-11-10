/* O tipo ab_int já foi definido. */
/* A função mostra_arvore já foi definida. */
/* A função rotaciona_esquerda já foi definida. */
/* A função rotaciona_direita já foi definida. */

#include <stdlib.h>
#include <stdio.h>

#ifdef MY_PC
/**
	Código de testes para ser rodado na máquina local
	Compilar com: gcc -Wall -ansi -DMY_PC 1 2_1.c
*/

typedef struct ab_int {
    int dado;
    struct ab_int *esq; 
    struct ab_int *dir; 
} ab_int;

ab_int* cria_arvore(int dado) {
	ab_int* p = calloc(1, sizeof(ab_int));
	if (p) {
		p->dado = dado;
	}
	return p;
}

void limpa_arvore(ab_int** raiz) {
	if (raiz && *raiz) {
		limpa_arvore(&(*raiz)->esq);
		limpa_arvore(&(*raiz)->dir);
		free(*raiz);
		*raiz = NULL;
	}
}

void mostra_arvore(ab_int* raiz) {
    printf("(");
    if (raiz) {
        printf("%d ", raiz->dado);
        mostra_arvore(raiz->esq);
        printf(" ");
        mostra_arvore(raiz->dir);
    } 
    printf(")");
}

int ___rd = 0;

void rotaciona_direita(ab_int **p_raiz) {
    ab_int *a, *b;
	if (!p_raiz || !*p_raiz) return;
	a = *p_raiz;
	b = a->esq;
	if (!b) return;
	___rd++;
	a->esq = b->dir;
	b->dir = a;
	*p_raiz = b;
}


int ___re = 0;

void rotaciona_esquerda(ab_int **p_raiz) {
    ab_int *a, *b;
	if (!p_raiz || !*p_raiz) return;
	a = *p_raiz;
	b = a->dir;
	if (!b) return;
	___re++;
	a->dir = b->esq;
	b->esq = a;
	*p_raiz = b;
}

char le_char(char** in) {
	char c = **in;
	*in = (*in)+1;
	return c;
}

ab_int* le_arvore(char** in) {
	if (le_char(in) == '(') {
		ab_int* raiz = NULL;
		char c = **in;
		if (c != ')') {
            int n;
            sscanf(*in, "%d", &n);
			raiz = cria_arvore(n);
            while( (c =**in) && c != '(') {
                *in = (*in)+1;
            }
			raiz->esq = le_arvore(in);
			raiz->dir = le_arvore(in);
			le_char(in);
		} else *in = (*in)+1;
		return raiz;
	}
	return NULL;
}

void dsw(ab_int **p_raiz);

#define do_it(f)    \
    dsw(&f);\
	printf("%d rotacoes a esquerda\n%d rotacoes a direita\n", ___re, ___rd); \
    mostra_arvore(f); printf("\n");\
	___re =0; ___rd = 0;

int main () {
	
	char *in_a1 = "(1()(2()(3()())))";
	char *in_a2 = "(10(9(8(7(6(5(4(3(2(1()())())())())())())())())())())";
	
	ab_int* a1 = le_arvore(&in_a1);
	ab_int* a2 = le_arvore(&in_a2);
	
    mostra_arvore(a1);printf("\n");
    do_it(a1);
    do_it(a1);
    mostra_arvore(a2);printf("\n");
    do_it(a2);

	limpa_arvore(&a1);	
	limpa_arvore(&a2);
	
	return 0;
}


#endif

void em_lista_d(ab_int **p_raiz) {
	if (p_raiz && *p_raiz) {
		em_lista_d(&(*p_raiz)->dir);
		if ((*p_raiz)->esq) {
			rotaciona_direita(p_raiz);
			em_lista_d(p_raiz);
		}
	} 
}

void comprime_d(ab_int **p_raiz, int rotacoes) {
    if (p_raiz && *p_raiz && rotacoes > 0) {
        rotaciona_esquerda(p_raiz);
        comprime_d(&((*p_raiz)->dir), rotacoes-1);
    }
}

int linha(ab_int *p_raiz) {
    if (p_raiz)
        return 1 + linha(p_raiz->dir);
    return 0;
}

void dsw(ab_int **p_raiz) {
    if (p_raiz && *p_raiz) {
        em_lista_d(p_raiz);
        int n = linha(*p_raiz);
        while (n-1) {
            comprime_d(p_raiz, (n-1)/2);
            n=(n+1)/2;
        }
    }
}