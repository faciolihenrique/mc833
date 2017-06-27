/* 2017
 * Projeto 2 - mc833 - Laboratório de Redes
 * linked_list.c
 * Implement
 * Henrique Noronha Facioli - 157986
 * Thiago Silva de Farias - 148077
 */

#include "linked_list.h"

void addElement(ListaAdj* List, Vehicle v) {
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

int isEmpty(ListaAdj* List) {
    if(List->cabeca == NULL)
        return 1;
    else
        return 0;
}

void free_list(ListaAdj* List) {
    if(!isEmpty(List)){
        No *proxNode, *atual;

        atual = List->cabeca;
        while(atual != NULL){
            proxNode = atual->prox;
            free(atual);
            atual = proxNode;
        }
    }
}
