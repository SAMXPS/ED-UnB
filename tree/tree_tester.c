/* O tipo ab_char já foi definido. */
/* A função mostra_arvore já foi definida. */
/* A função rotaciona_esquerda já foi definida. */

#include <stdlib.h>
#include <stdio.h>

#ifdef MY_PC
/**
	Código de testes para ser rodado na máquina local
	Compilar com: gcc -Wall -ansi -DMY_PC 1 2_1.c
*/

typedef struct ab_char {
    char dado;
    struct ab_char *esq; 
    struct ab_char *dir; 
} ab_char;

ab_char* cria_arvore(char dado) {
	ab_char* p = calloc(1, sizeof(ab_char));
	if (p) {
		p->dado = dado;
	}
	return p;
}

void limpa_arvore(ab_char** raiz) {
	if (raiz && *raiz) {
		limpa_arvore(&(*raiz)->esq);
		limpa_arvore(&(*raiz)->dir);
		free(*raiz);
		*raiz = NULL;
	}
}

void mostra_arvore(ab_char* raiz) {
    printf("(");
    if (raiz) {
        printf("%c ", raiz->dado);
        mostra_arvore(raiz->esq);
        printf(" ");
        mostra_arvore(raiz->dir);
    } 
    printf(")");
}

int ___re = 0;

void rotaciona_esquerda(ab_char **p_raiz) {
    ab_char *a, *b;
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

ab_char* le_arvore(char** in) {
	if (le_char(in) == '(') {
		ab_char* raiz = NULL;
		char c = le_char(in);
		if (c != ')') {
			raiz = cria_arvore(c);
			raiz->esq = le_arvore(in);
			raiz->dir = le_arvore(in);
			le_char(in);
		}
		return raiz;
	}
	return NULL;
}

void em_lista(ab_char **p_raiz);
#define printa(f) 	mostra_arvore(f);\
	printf("\n");\
	printf("rotacoes executadas: %d\n", ___re); \
	___re =0;
int main () {
	
	char *in_outra_raiz = "(a(b()())(c()()))";
	char *in_raiz = "(I(H()(J()()))(G(F(E()())(D()()))(C(B()())(A()()))))";
	
	ab_char* outra_raiz = le_arvore(&in_outra_raiz);
	ab_char* raiz = le_arvore(&in_raiz);
	
	mostra_arvore(outra_raiz);
	printf("\n");
	mostra_arvore(raiz);
	printf("\n");
	
	em_lista(NULL);
	printa(NULL);
	
	em_lista(&(outra_raiz->esq));
	printa(outra_raiz);

	
	em_lista(&(outra_raiz->dir));
	printa(outra_raiz);
	
	em_lista(&outra_raiz);
	printa(outra_raiz);
	
	em_lista(&(raiz->esq));
	printa(raiz);
	
	em_lista(&(raiz->dir));
	printa(raiz);
	 	

	em_lista(&raiz);
	printa(raiz);
	
	limpa_arvore(&outra_raiz);	
	limpa_arvore(&raiz);
	
	return 1;
}


#endif

void em_lista(ab_char **p_raiz) {
	if (p_raiz && *p_raiz) {
		if ((*p_raiz)->esq) em_lista(&(*p_raiz)->esq);
		if ((*p_raiz)->dir) {
			rotaciona_esquerda(p_raiz);
			em_lista(p_raiz);
		}
	} 
}
