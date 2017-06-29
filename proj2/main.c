/* 2017
 * Projeto 2 - mc833 - Laboratório de Redes
 * main.c
 *
 * Henrique Noronha Facioli - 157986
 * Thiago Silva de Farias - 148077
 */

#include <time.h>
#include <sys/types.h>
#include <signal.h>

#include "main.h"
#include "server.h"
#include "simulation.h"
#include "printing.h"

unsigned long int time_running = 0;
unsigned long int ambulances = 0;
unsigned long int c_continue = 0;
unsigned long int c_incraese_speed = 0;
unsigned long int c_decrease_speed = 0;

pid_t pids[3];

////////////////////////////////////////////////////////////////////////////////

int main() {
    AdjList* CarList = malloc(sizeof(AdjList));
    CarList->cabeca = NULL;

    /* Time to send a signal to the simulation */
    struct timespec ts;
    ts.tv_sec = 100 / 1000;
    ts.tv_nsec = (100 % 1000) * 1000000;

    create_router();    //  Inicializa o roteador (criando um servidor de security, media, confort)

#ifdef NCURSES_SIMULATE
    initscr();			                          /* Start curses mode */
#endif

    while(simulate(CarList)){
        nanosleep(&ts, NULL);
    }

    endProgram(CarList);

    printf("Colisões: %lu\n", ambulances);
    printf("Comandos emitidos:\n\tContinuar: %lu\n\tAumentar: %lu\n\tDiminuir: %lu\n", c_continue, c_incraese_speed, c_decrease_speed);

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

void endProgram(AdjList* List){

#ifdef NCURSES_SIMULATE
    endwin();
#endif

    kill(pids[0], SIGKILL);
    kill(pids[1], SIGKILL);
    kill(pids[2], SIGKILL);

    free_list(List);

    sleep(1);
}
