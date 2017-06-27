#include "main.h"

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* Node struct */
typedef struct No {
    Vehicle v;
    struct No* prox;
} No;

/* Adjacency List struct */
typedef struct {
    struct No* cabeca;
} AdjList;

/* Map */
int map[SIZE_MAP][SIZE_MAP];

/* Add an element to the list */
void addElement(AdjList* List, Vehicle v);

/* Checks if the list is empty */
int isEmpty(AdjList* List);

/* Removes the vehicle v from the list */
void removeElement(AdjList* List, Vehicle v);

/* Frees the memory used by the list */
void free_list(AdjList* List);

#endif
