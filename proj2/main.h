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

#include "definitions.h"

/* Simulation */
#define SIZE_CAR 1
#define SIZE_TRUCK 2
#define SIZE_DOUBLETRUCK 3

/* Conections definitons */

#define MAX_PENDING 5
#define MAX_LINE 2048


/* "Define" a type just to make it more readable */
#define Speed int
#define Timestamp unsigned long int

/*~~~~~~ Data Structures ~~~~~~~*/
typedef enum {Car, Truck, DoubleTruck} CarType;
typedef enum {North, West, South, East} Direction;
typedef enum {Confort, Entertainment, Security} ConectionType;
typedef enum {None, Continue, Increase, Decrease, Ambulance} Action;

/* Position struct */
typedef struct {
    int x;
    int y;
} Position;

/* Vehicle struct */
typedef struct {
    char symbol;
    int ID;
    CarType type;
    int length;
    Speed car_speed;
    Direction dir;
    Position pos;
    Timestamp entry_time;
} Vehicle;

typedef struct {
    int ID;
    CarType type;
    int length;
    Position pos;
    Direction dir;
    Speed car_speed;
    Timestamp time_rec;
    Timestamp estimated_time_in1;
    Timestamp estimated_time_out1;
    Timestamp estimated_time_in2;
    Timestamp estimated_time_out2;
    Timestamp destroy;
} ServerCar;

/* Package struct */
typedef struct {
    int ID;
    CarType type;
    int length;
    Position pos;
    Direction dir;
    Speed car_speed;
    Timestamp time_sent;
} SecPackageToServer;

typedef struct {
    int ID;
    Speed car_speed;
    Action ac;
} SecPackageToClient;

void endProgram();

#endif
