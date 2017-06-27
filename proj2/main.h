/* main header
 *
 * Contains things that are shared between all the modules of the project
 *
 */
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <uchar.h>

#include "definitions.h"

/* Simulation */
#define SIZE_CAR 1
#define SIZE_TRUCK 2
#define SIZE_DOUBLETRUCK 3

/* Conections definitons */

#define ENT_PORT 42000
#define SEC_PORT 43000
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

/* Vehicle struct */
typedef struct {
    int ID;
    CarType type;
    int length;
    Speed car_speed;
    Direction dir;
    Position pos;
} Vehicle;

/* Package struct */
typedef struct {
    Position pos;
    Direction dir;
    Speed car_speed;
} Package;

#endif
