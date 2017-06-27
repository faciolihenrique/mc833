#include "main.h"

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* Node struct */
typedef struct No {
    void  *v;
    struct No* prox;
} No;

/* Adjacency List struct */
typedef struct {
    struct No* cabeca;
} AdjList;

/* Checks if the list is empty */
int isEmpty(AdjList* List);
/* Frees the memory used by the list */
void free_list(AdjList* List);


/* Add an element to the list */
void addVehicleList(AdjList* List, Vehicle* v);
/* Removes the vehicle v from the list */
void removeVehicleList(AdjList* List, int ID);

/* Add an element to the list */
void addServerCarList(AdjList* List, ServerCar* v);
/* Removes the vehicle v from the list */
void removeServerCarList(AdjList* List, int ID);



#endif
