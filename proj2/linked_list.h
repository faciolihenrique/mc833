#include "main.h"

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct No {
    Vehicle v;
    struct No* prox;
} No;

typedef struct {
    No* cabeca;
} ListaAdj;

int map[SIZE_MAP][SIZE_MAP];

void addElement(ListaAdj* List, Vehicle v);

int isEmpty(ListaAdj* List);

void removeElent(ListaAdj* List, Vehicle v);

void free_list(ListaAdj* List);

#endif
