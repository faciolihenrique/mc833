/* 2017
 * Projeto 2 - mc833 - Laboratório de Redes
 * linked_list.c
 * 
 * Henrique Noronha Facioli - 157986
 * Thiago Silva de Farias - 148077
 */

#include "linked_list.h"

void addElement(AdjList* List, Vehicle v) {
    No *novo = (No *) malloc(sizeof(No));
    if(!novo){
        printf("Sem memoria disponivel!\n");
        exit(1);
    }

    /* Creates the node */
    novo->v = v;
    novo->prox = NULL;

    if( isEmpty(List) ) {
        List->cabeca = novo;
    }
    else{
        No *tmp = List->cabeca;
        while(tmp->prox != NULL) {
            tmp = tmp->prox;
        }
        tmp->prox = novo;
    }
}

int isEmpty(AdjList* List) {
    if(List->cabeca == NULL)
        return 1;
    else
        return 0;
}

void removeElement(AdjList* List, Vehicle v) {
    if(!isEmpty(List)){
        No *anterior = List->cabeca;
        No *atual = anterior->prox;
        while (anterior != NULL && atual != NULL) {
            if (atual->v.ID == v.ID) {
                No *temp = atual;
                anterior->prox = atual->prox;
                free(temp);
                return;
            }
        anterior = atual;
        atual = atual->prox;
        }
    }
}

void free_list(AdjList* List) {
    if(!isEmpty(List)){
        No *proxNo, *atual;

        atual = List->cabeca;
        while(atual != NULL){
            proxNo = atual->prox;
            free(atual);
            atual = proxNo;
        }
    }
}
