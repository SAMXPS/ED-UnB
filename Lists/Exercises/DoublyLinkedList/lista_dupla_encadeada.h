/**      @file: lista_dupla_encadeada.h
 *     @author: Guilherme N. Ramos (gnramos@unb.br)
 * @disciplina: Estruturas de Dados
 *
 * Definição das estruturas e funções para lidar com lista encadeada simples.
 * Assume que o tipo de dado info_t já foi definido. */

#ifndef UNB_CIC_ED_LISTA_DUPLA_ENCADEADA_H
#define UNB_CIC_ED_LISTA_DUPLA_ENCADEADA_H

typedef struct elemento_t {
    info_t info;
    struct elemento_t* prox; /* Ponteiro para o próximo elemento. */
    struct elemento_t* ant;  /* Ponteiro para o elemento anterior. */
} elemento_t;                /* Determina um elemento (nó) da lista. */

typedef elemento_t lista_t; /* A lista é uma sequência de elementos. */

/* Cria, dinamicamente, um novo elemento com os argumentos dados. */
elemento_t* elemento(const info_t* info, elemento_t* prox, elemento_t* ant);

/* Libera o elemento criado dinamicamente, e define o conteúdo do ponteiro como
NULL. */
void libera(elemento_t** ptr);

#include "lista.h"

#endif /* UNB_CIC_ED_LISTA_DUPLA_ENCADEADA_H */