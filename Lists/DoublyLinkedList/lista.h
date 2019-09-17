/**      @file: lista_.h
 *     @author: Guilherme N. Ramos (gnramos@unb.br)
 * @disciplina: Estruturas de Dados
 *
 * Definição das operações básicas de uma lista. Assume que já foram definidos
 * os seguintes tipos de dados:
 *    - info_t: que determina o dado a ser armazenado.
 *    - elemento_t: que determina um elemento (nó) da lista.
 *    - lista_t: que implementa a lista. */


#ifndef UNB_CIC_ED_LISTA_H
#define UNB_CIC_ED_LISTA_H

#include <stdbool.h>

/* Busca a informação nos elementos da lista. Retorna o ponteiro para o elemento
que a contem, se houver, NULL caso contrário. */
elemento_t* busca(const info_t *info, lista_t* lista);

/* Esvazia a lista. */
void esvazia(lista_t **ptr_lista);

/* Compara duas informações armazenadas i1 e i2.  Retorna um inteiro menor que,
igual a, ou maior que zero se i1 for, respectivamente, menor que, igual a, ou
maior que i2. */
int infocmp(const info_t* i1, const info_t* i2);

/* Compara dois elementos e1 e e2.  Retorna um inteiro menor que, igual a, ou
maior que zero se e1 for, respectivamente, menor que, igual a, ou maior que e2. */
int elementocmp(const elemento_t* e1, const elemento_t* e2);

/* Insere o elemento dado na lista, na posição indicada (base 0). Retorna um
booleano indicando se a inserção foi bem sucedida. */
_Bool insere(elemento_t* e, unsigned int pos, lista_t** ptr_lista);

/* Insere o elemento dado na lista, em ordem crescente dos elementos. Retorna um
booleano indicando se a inserção foi bem sucedida. */
_Bool insere_em_ordem(elemento_t* e, lista_t** ptr_lista);

/* Retira o elemento da posição dada da lista (base 0). Retorna o ponteiro para
este elemento, se foi bem sucedida, NULL caso contrário. */
elemento_t* retira(unsigned int pos, lista_t** ptr_lista);

/* Retira a primeira ocorrência da informação dada da lista. Retorna o ponteiro
para este elemento, se foi bem sucedida, NULL caso contrário. */
elemento_t* retira_em_ordem(info_t* info, lista_t** ptr_lista);

/* Retorna a quantidade de elementos na lista. */
unsigned int tamanho(const lista_t* lista);

/* Indica se a lista está vazia ou não. */
_Bool vazia(const lista_t *lista);

/* Mostra a informação na saída padrão. */
void print_i(const info_t* info);

/* Mostra o elemento na saída padrão. */
void print_e(const elemento_t* e);

/* Mostra a lista na saída padrão. */
void print_l(const lista_t* lista);

#endif