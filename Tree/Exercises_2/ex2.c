/* O tipo ab_int já foi definido. */
/* A função mostra_arvore já foi definida. */
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

void le_mostra_arvore(ab_int* raiz) {
    printf("(");
    if (raiz) {
        printf("%d ", raiz->dado);
        le_mostra_arvore(raiz->esq);
        printf(" ");
        le_mostra_arvore(raiz->dir);
    } 
    printf(")");
}

int ___re = 0;

void rotaciona_direita(ab_int **p_raiz) {
    ab_int *a, *b;
	if (!p_raiz || !*p_raiz) return;
	a = *p_raiz;
	b = a->esq;
	if (!b) return;
	___re++;
	a->esq = b->dir;
	b->dir = a;
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

void comprime(ab_int **p_raiz, int rotacoes);

#define mostra_arvore(f) 	le_mostra_arvore(f);\
	printf("\n");\
	printf("rotacoes executadas: %d\n", ___re); \
	___re =0;

int main () {
	
	char *in_outra_raiz = "(2(1()())(3()()))";
	char *in_raiz = "(10(9(8(7(6(5(4(3(2(1()())())())())())())())())())())";
	
	ab_int* outra_raiz = le_arvore(&in_outra_raiz);
	ab_int* raiz_1 = le_arvore(&in_raiz);
	
    comprime(&outra_raiz, 1);
    mostra_arvore(outra_raiz);

    comprime(&raiz_1, 0);
    mostra_arvore(raiz_1);

    comprime(&raiz_1, 4);
    mostra_arvore(raiz_1);

	limpa_arvore(&outra_raiz);	
	limpa_arvore(&raiz_1);
	
	return 0;
}


#endif

void comprime(ab_int **p_raiz, int rotacoes) {
    if (p_raiz && *p_raiz && rotacoes > 0) {
        rotaciona_direita(p_raiz);
        comprime(&((*p_raiz)->esq), rotacoes-1);
    }
}