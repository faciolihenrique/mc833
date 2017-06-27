/* 2017
 * Projeto 2 - mc833 - Laboratório de Redes
 * printing.c
 *
 * Henrique Noronha Facioli - 157986
 * Thiago Silva de Farias - 148077
 */

#include "printing.h"

int row, col;

////////////////////////////////////////////////////////////////////////////////

void printMap(char map[SIZE_MAP][SIZE_MAP]) {
    int i, j, l, m;

    getmaxyx(stdscr,row,col);

    for (l = 0, i = (row-SIZE_MAP)/2; i < (row+SIZE_MAP)/2; i++,l++) {
        for (m = 0, j = (col-SIZE_MAP)/2; j < (col+SIZE_MAP)/2; j++, m++) {
            mvprintw(i, j, "%c", map[l][m]);
        }
    }
    refresh();			        /* Print it on to the real screen */
}

////////////////////////////////////////////////////////////////////////////////
