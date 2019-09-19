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
    elemento_t* e = malloc(sizeof(elemento_t));
    if (e) {
        e->info = *info;
        e->ant = ant;
        e->prox = prox;
    }
    return e;
}

void libera(elemento_t** ptr) {
    if (*ptr) {
        free(*ptr);
    }
    *ptr = NULL;
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
    if (pos > 1) {
        return *ptr_lista && insere(e, pos-1, &((*ptr_lista)->prox));
    } else if (e) {
        if (pos == 0) {
            e->ant = NULL;
            e->prox = *ptr_lista;
            *ptr_lista = e;
        } else /*if (pos == 1) always true at this point*/ {
            e->ant = *ptr_lista;
            e->prox = (*ptr_lista)->prox;
            (*ptr_lista)->prox = e;
        }
        if (e->prox)
            e->prox->ant = e;
        return true;
    }
    return false;
}

_Bool insere_em_ordem(elemento_t* e, lista_t** ptr_lista){
    if (!*ptr_lista) {
        return insere(e, 0, ptr_lista);
    } else if (e) {
        int c = elementocmp(e, *ptr_lista);
        if (c > 0) {
            if ((*ptr_lista)->prox)
                return insere_em_ordem(e, &(*ptr_lista)->prox);
            else return insere(e, 1, ptr_lista);
        } else if ((*ptr_lista)->ant) {
            return insere(e, 1, &(*ptr_lista)->ant);
        } else return insere(e, 0, ptr_lista);
    }
    return false;
}

elemento_t* retira(unsigned int pos, lista_t** ptr_lista) {
    if (!*ptr_lista) return NULL;
    elemento_t *e;
    if (pos == 0) {
        e = *ptr_lista;
        *ptr_lista = e->prox;
        if (e->prox) {
            e->prox->ant = NULL;
        }
    } else if (pos == 1) {
        e = (*ptr_lista)->prox;
        if (e) {
            (*ptr_lista)->prox = e->prox;
            if (e->prox) {
                e->prox->ant = *ptr_lista;
            }
        }
    } else {
        return retira(pos-1, &(*ptr_lista)->prox);
    }
    return e;
}

elemento_t* retira_em_ordem(info_t* info, lista_t** ptr_lista) {
    elemento_t *e = busca(info, *ptr_lista);
    if (e) {
        if (e->ant)
            e->ant->prox= e->prox;
        else
            *ptr_lista = e->prox;

        if (e->prox)
            e->prox->ant= e->ant;
    }
    return e;
}

void esvazia(lista_t** ptr_lista) {
    if (*ptr_lista) {
        esvazia(&((*ptr_lista)->prox));
        libera(ptr_lista);
    }
}

elemento_t* busca(const info_t *info, lista_t* lista) {
    if (lista) {
        return !infocmp(info, &lista->info) ? lista : busca(info, lista->prox);
    } else return NULL;
}

unsigned int tamanho(const lista_t* lista) {
    if (!lista) return 0;
    return 1 + tamanho(lista->prox);
}

_Bool vazia(const lista_t *lista) {
    return !tamanho(lista);
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