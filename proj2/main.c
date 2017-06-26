/* 2017
 * Projeto 2 - mc833 - Laboratório de Redes
 * main.c
 *
 * Henrique Noronha Facioli - 157986
 * Thiago Silva de Farias - 148077
 */

#include "main.h"
#include "servidor.h"
#include "simulacao.h"

int main() {
    create_router();    // Inicializa o roteador (criando um servidor de media, security, confort)
    create_car();       // Inicializa alguns carros
    while(1){
        sleep(1);
        simulate();
    }
    return 0;
}
