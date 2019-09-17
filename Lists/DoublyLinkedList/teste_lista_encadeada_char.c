/**      @file: lista_encadeada_char.c
 *     @author: Guilherme N. Ramos (gnramos@unb.br)
 * @disciplina: Estruturas de Dados
 *
 * Teste da implementação das funções para lidar com lista duplamente encadeada
 * contendo um caractere. */

#include <assert.h>
#include <stdlib.h>

#include "lista_encadeada_char.h"

void testa_infocmp() {
    char e1 = 'a', e2 = 'a';

    assert(0 == infocmp(NULL, NULL));
    assert(0 < infocmp(&e1, NULL));
    assert(0 > infocmp(NULL, &e2));
    assert(0 == infocmp(&e1, &e2));

    e2 = 'b';
    assert(0 > infocmp(&e1, &e2));
    assert(0 < infocmp(&e2, &e1));
}

void testa_elementocmp() {
    elemento_t e1 = {.info = 'a', .prox = NULL, .ant = NULL};
    elemento_t e2 = {.info = 'a', .prox = &e1, .ant = NULL};
    e1.ant = &e2;

    assert(0 == elementocmp(NULL, NULL));
    assert(0 < elementocmp(&e1, NULL));
    assert(0 > elementocmp(NULL, &e2));
    assert(0 == elementocmp(&e1, &e2));

    e2.info = 'b';
    assert(0 > elementocmp(&e1, &e2));
    assert(0 < elementocmp(&e2, &e1));
}

void testa_elemento() {
    char info = 'a';
    elemento_t* e1 = elemento(&info, NULL, NULL);

    assert(e1);
    assert(e1->info == 'a');
    assert(e1->prox == NULL);
    assert(e1->ant == NULL);
    libera(&e1);

    info = 'b';
    elemento_t* e2 = elemento(&info, e1, NULL);
    assert(e2);
    assert(e2->info == 'b');
    assert(e2->prox == e1);
    assert(e2->ant == NULL);
    libera(&e2);
}

void testa_libera() {
    char info = 'a';
    elemento_t* e = elemento(&info, NULL, NULL);

    assert(e);
    libera(&e);
    assert(!e);
}

void testa_vazia() {
    char info = 'a';
    elemento_t* lista = elemento(&info, NULL, NULL);

    assert(vazia(NULL));
    assert(!vazia(lista));
    libera(&lista);
    assert(vazia(NULL));
}

void testa_insere() {
    assert(!insere(NULL, 0, NULL));

    lista_t* lista = NULL;
    assert(!insere(NULL, 0, &lista));

    char info = 'c';
    elemento_t* e3 = elemento(&info, NULL, NULL);
    assert(!insere(e3, -1, &lista));
    assert(!insere(e3, 7, &lista));
    assert(insere(e3, 0, &lista));
    assert(lista);
    assert(0 == elementocmp(lista, e3));

    info = 'a';
    elemento_t* e1 = elemento(&info, NULL, NULL);
    assert(insere(e1, 0, &lista));
    assert(0 == elementocmp(lista, e1));
    assert(lista->prox == e3);
    assert(e3->ant == lista);

    info = 'b';
    elemento_t* e2 = elemento(&info, NULL, NULL);
    assert(insere(e2, 1, &lista));
    assert(0 == elementocmp(lista, e1));
    assert(lista->prox == e2);
    assert(e2->ant == lista);
    assert(e2->prox == e3);
    assert(e3->ant == e2);

    info = 'd';
    elemento_t* e4 = elemento(&info, NULL, NULL);
    assert(insere(e4, 3, &lista));
    assert(0 == elementocmp(lista, e1));
    assert(lista->prox == e2);
    assert(e2->prox == e3);
    assert(e2->ant == lista);
    assert(e3->prox == e4);
    assert(e3->ant == e2);
    assert(e4->prox == NULL);
    assert(e4->ant == e3);

    esvazia(&lista);
}

void testa_insere_em_ordem() {
    lista_t* lista = NULL;
    assert(!insere_em_ordem(NULL, &lista));

    char info = 'c';
    elemento_t* e3 = elemento(&info, NULL, NULL);
    assert(insere_em_ordem(e3, &lista));
    assert(lista);
    assert(0 == elementocmp(lista, e3));

    info = 'a';
    elemento_t* e1 = elemento(&info, NULL, NULL);
    assert(insere_em_ordem(e1, &lista));
    assert(0 == elementocmp(lista, e1));
    assert(lista->prox == e3);
    assert(e3->ant == lista);

    info = 'b';
    elemento_t* e2 = elemento(&info, NULL, NULL);
    assert(insere_em_ordem(e2, &lista));
    assert(0 == elementocmp(lista, e1));
    assert(lista->prox == e2);
    assert(e2->prox == e3);
    assert(e3->ant == e2);

    info = 'd';
    elemento_t* e4 = elemento(&info, NULL, NULL);
    assert(insere_em_ordem(e4, &lista));
    assert(0 == elementocmp(lista, e1));
    assert(lista->prox == e2);
    assert(e2->prox == e3);
    assert(e2->ant == lista);
    assert(e3->prox == e4);
    assert(e3->ant == e2);
    assert(e4->prox == NULL);
    assert(e4->ant == e3);

    esvazia(&lista);
}

void testa_retira() {
    lista_t* lista = NULL;

    assert(!retira(0, &lista));

    char info = 'c';
    insere(elemento(&info, NULL, NULL), 0, &lista);
    info = 'b';
    insere(elemento(&info, NULL, NULL), 0, &lista);
    info = 'a';
    insere(elemento(&info, NULL, NULL), 0, &lista);

    elemento_t* e = retira(1, &lista);
    assert(e);
    assert('b' == e->info);
    assert(2 == tamanho(lista));
    assert('a' == lista->info);
    assert('c' == lista->prox->info);
    assert(lista == lista->prox->ant);
    libera(&e);

    e = retira(1, &lista);
    assert(e);
    assert('c' == e->info);
    assert(1 == tamanho(lista));
    assert('a' == lista->info);
    assert(NULL == lista->prox);
    libera(&e);

    e = retira(0, &lista);
    assert(e);
    assert('a' == e->info);
    assert(vazia(lista));
}

void testa_retira_em_ordem() {
    lista_t* lista = NULL;

    assert(!retira_em_ordem(0, &lista));

    char info = 'c';
    insere_em_ordem(elemento(&info, NULL, NULL), &lista);
    info = 'a';
    insere_em_ordem(elemento(&info, NULL, NULL), &lista);
    info = 'b';
    insere_em_ordem(elemento(&info, NULL, NULL), &lista);

    info = 'd';
    assert(!retira_em_ordem(&info, &lista));

    info = 'b';
    elemento_t* e = retira_em_ordem(&info, &lista);
    assert(e);
    assert('b' == e->info);
    assert(2 == tamanho(lista));
    assert('a' == lista->info);
    assert('c' == lista->prox->info);
    assert(lista == lista->prox->ant);
    libera(&e);

    info = 'c';
    e = retira_em_ordem(&info, &lista);
    assert(e);
    assert('c' == e->info);
    assert(1 == tamanho(lista));
    assert('a' == lista->info);
    assert(NULL == lista->prox);
    libera(&e);

    info = 'a';
    e = retira_em_ordem(&info, &lista);
    assert(e);
    assert(1 == e->info);
    assert(vazia(lista));
}

void testa_esvazia() {
    char info = 'c';
    lista_t* lista = NULL;

    insere(elemento(&info, NULL, NULL), 0, &lista);
    assert(lista);
    insere(elemento(&info, NULL, NULL), 0, &lista);
    assert(lista->prox);
    assert(!(lista->prox->prox));
    esvazia(&(lista->prox));
    assert(lista);
    assert(vazia(lista->prox));

    insere(elemento(&info, NULL, NULL), 0, &lista);
    esvazia(&lista);
    assert(vazia(lista));
}

void testa_busca() {
    lista_t* lista = NULL;

    char info = 'c';
    insere(elemento(&info, NULL, NULL), 0, &lista);
    info = 'b';
    insere(elemento(&info, NULL, NULL), 0, &lista);
    info = 'a';
    insere(elemento(&info, NULL, NULL), 0, &lista);

    info = 0;
    assert(!busca(&info, lista));
    info = 'a';
    assert(busca(&info, lista));
    info = 'b';
    assert(busca(&info, lista));
    info = 'c';
    assert(busca(&info, lista));
    info = 'd';
    assert(!busca(&info, lista));

    esvazia(&lista);
}

void testa_tamanho() {
    char info = 'c';
    lista_t* lista = NULL;

    assert(0 == tamanho(lista));
    insere(elemento(&info, NULL, NULL), 0, &lista);
    assert(1 == tamanho(lista));
    assert(0 == tamanho(lista->prox));
    insere(elemento(&info, NULL, NULL), 0, &lista);
    assert(2 == tamanho(lista));
    assert(1 == tamanho(lista->prox));
    assert(0 == tamanho(lista->prox->prox));
    insere(elemento(&info, NULL, NULL), 0, &lista);
    assert(3 == tamanho(lista));
    assert(2 == tamanho(lista->prox));
    assert(1 == tamanho(lista->prox->prox));
    assert(0 == tamanho(lista->prox->prox->prox));

    esvazia(&lista);
}

int main() {
    testa_infocmp();
    testa_elementocmp();
    testa_elemento();
    testa_libera();
    testa_vazia();
    testa_insere();
    testa_insere_em_ordem();
    testa_retira();
    testa_retira_em_ordem();
    testa_esvazia();
    testa_busca();
    testa_tamanho();

    return 0;
}