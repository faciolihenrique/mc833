#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* Definitions */
#define SIZE_MAP 18

/* Simulation */
#define SIZE_CAR 1
#define SIZE_TRUCK 2
#define SIZE_DOUBLETRUCK 3
#define MAX_SPEED 3

#define SPEED_MULTIPLIER 1

/* Conections definitons */
#define N_CONNECTIONS 20
#define SEC_PORT 42000
#define ENT_PORT 43000
#define CON_PORT 44000

#define PKG_ENT_SIZE
#define PKG_SEC_SIZE
#define PKG_CON_SIZE

#define MAX_PENDING 5
#define MAX_LINE 2048


/* "Define" a type just to make it more readable */
#define Speed int

/*~~~~~~ Data Structures ~~~~~~~*/
typedef enum {Car, Truck, DoubleTruck} CarType;
typedef enum {North, West, South, East} Direction;

/* Position struct */
typedef struct {
    int x;
    int y;
} Position;

/* Vehicle */
typedef struct {
    CarType type;
    int length;
    Speed car_speed;
    Direction dir;
    Position pos;
} Vehicle;

/* Package sent */
typedef struct {
    Position pos;
    Direction dir;
    Speed car_speed;
} Package;

struct No {
    Vehicle* v;
    struct No* prox;
};

struct ListaAdj {
    struct No *cabeca;
};

int map[SIZE_MAP][SIZE_MAP];

#endif
