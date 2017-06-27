/* 2017
 * Projeto 2 - mc833 - Laboratório de Redes
 * main.c
 *
 * Henrique Noronha Facioli - 157986
 * Thiago Silva de Farias - 148077
 */

#include <time.h>

#include "main.h"
#include "server.h"
#include "simulation.h"
#include "printing.h"



int main() {
    struct timespec ts;
    ts.tv_sec = 1000 / 1000;
    ts.tv_nsec = (1000 % 1000) * 1000000;

    initscr();			        /* Start curses mode 		  */

    AdjList* CarList = malloc(sizeof(AdjList));

    create_router();    //  Inicializa o roteador (criando um servidor de security, media, confort)
    printf("\n");

    while(1){
        nanosleep(&ts, NULL);
        simulate(CarList);
    }
    return 0;
}
