/**      @file: lista_encadeada_char.c
 *     @author: Guilherme N. Ramos (gnramos@unb.br)
 * @disciplina: Estruturas de Dados
 *
 * Implementação das funções para lidar com lista duplamente encadeada contendo
 * um caractere. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_encadeada_char.h"

elemento_t* elemento(const info_t* info, elemento_t* ant, elemento_t* prox) {
    /* Insira seu código aqui. */
}

void libera(elemento_t** ptr) {
    /* Insira seu código aqui. */
}

int infocmp(const info_t* e1, const info_t* e2) {
    if (e1 == e2) return 0;
    if (!e1) return -1;
    if (!e2) return 1;
    return (*e1) - (*e2);
}

int elementocmp(const elemento_t* e1, const elemento_t* e2) {
    if (e1 == e2) return 0;
    if (!e1) return -1;
    if (!e2) return 1;
    return infocmp(&(e1->info), &(e2->info));
}

_Bool insere(elemento_t* e, unsigned int pos, lista_t** ptr_lista) {
    /* Insira seu código aqui. */
}

_Bool insere_em_ordem(elemento_t* e, lista_t** ptr_lista){
    /* Insira seu código aqui. */
}

elemento_t* retira(unsigned int pos, lista_t** ptr_lista) {
    /* Insira seu código aqui. */
}

elemento_t* retira_em_ordem(info_t* info, lista_t** ptr_lista) {
    /* Insira seu código aqui. */
}

void esvazia(lista_t** ptr_lista) {
    /* Insira seu código aqui. */
}

elemento_t* busca(const info_t *info, lista_t* lista) {
    /* Insira seu código aqui. */
}

unsigned int tamanho(const lista_t* lista) {
    /* Insira seu código aqui. */
}

_Bool vazia(const lista_t *lista) {
    /* Insira seu código aqui. */
}

void print_i(const info_t* info) {
    if(info)
        printf("%c", *info);
}

void print_e(const elemento_t* e) {
    if(e) {
        printf("\tinfo: ");
        print_i(&(e->info));
        printf("\n\tprox: %p\n", e->prox);
        printf("\n\t ant: %p\n", e->ant);
    }
}

void print_l(const lista_t* lista) {
    int i = 0;
    while(lista) {
        printf("\n%d-esimo elemento:\n", i);
        print_e(lista);
        lista = lista->prox;
        ++i;
    }
}