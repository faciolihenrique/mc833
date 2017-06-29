/* 2017
 * Projeto 2 - mc833 - Laboratório de Redes
 * simulation.c
 *
 * Henrique Noronha Facioli - 157986
 * Thiago Silva de Farias - 148077
 */

#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "simulation.h"
#include "linked_list.h"
#include "printing.h"

char CrossMap[SIZE_MAP][SIZE_MAP];

extern unsigned long int time_running;
extern unsigned long int ambulances;
extern unsigned long int commands;

////////////////////////////////////////////////////////////////////////////////

int simulate(AdjList* CarList) {
#ifdef SIMULATE1
    if (time_running == 0) {
        addVehicleList(CarList, create_vehicle(1, Car, 1, North));
        addVehicleList(CarList, create_vehicle(2, Car, 1, West));
        addVehicleList(CarList, create_vehicle(3, Car, 1, South));
        addVehicleList(CarList, create_vehicle(4, Car, 1, East));
    }
#endif
#ifdef SIMULATE2
    if (time_running == 0) {
        addVehicleList(CarList, create_vehicle(1, Car, 1, North));
        addVehicleList(CarList, create_vehicle(2, Car, 1, West));
        addVehicleList(CarList, create_vehicle(3, Car, 1, East));
        addVehicleList(CarList, create_vehicle(4, Car, 1, South));
        addVehicleList(CarList, create_vehicle(5, DoubleTruck, 3, South));
        addVehicleList(CarList, create_vehicle(6, DoubleTruck, 2, West));
    }

    if (time_running == 50) {
        addVehicleList(CarList, create_vehicle(11, Car, 2, North));
        addVehicleList(CarList, create_vehicle(21, Car, 2, West));
        addVehicleList(CarList, create_vehicle(31, Car, 2, East));
        addVehicleList(CarList, create_vehicle(41, Car, 2, South));
        addVehicleList(CarList, create_vehicle(51, DoubleTruck, 3, South));
        addVehicleList(CarList, create_vehicle(61, DoubleTruck, 3, West));
    }
#endif


    update_cars(CarList);

#ifdef NCURSES_SIMULATE
    update_map(CarList, CrossMap);
    printMap(CrossMap);
#endif

    ++time_running;
    if(isEmpty(CarList)){
        return 0;
    }
    return 1;
}

////////////////////////////////////////////////////////////////////////////////

Vehicle* create_vehicle(int ID, CarType type, Speed car_speed, Direction dir) {
    Vehicle* v = calloc(1,sizeof(Vehicle));

    // ID.
    v->ID = ID;
    // CarType.
    v->type = type;
    // Length according to Type.
    if(type == Car) {
        v->length = SIZE_CAR;
        v->symbol = 'c';
    } else if(type == Truck) {
        v->length = SIZE_TRUCK;
        v->symbol = 't';
    } else if(type == DoubleTruck){
        v->length = SIZE_DOUBLETRUCK;
        v->symbol = 'd';
    }
    // Speed.
    if (car_speed >= 1 && car_speed <= MAX_SPEED) {
        v->car_speed = car_speed;
    } else {
        v->car_speed = MAX_SPEED;
    }
    // Direction.
    v->dir = dir;
    // Initial Position according to Direction.
    if(dir == North) {
        v->pos.y = (SIZE_MAP - 1) - v->length + 1;
        v->pos.x = SIZE_MAP/2;
    } else if(dir == West) {
        v->pos.y = (SIZE_MAP/2) - 1;
        v->pos.x = (SIZE_MAP - 1) - v->length + 1;
    } else if(dir == South) {
        v->pos.y = v->length - 1;
        v->pos.x = (SIZE_MAP/2) - 1;
    } else if(dir == East) {
        v->pos.y = SIZE_MAP/2;
        v->pos.x = v->length - 1;
    }

    v->entry_time = time_running;

    return v;
}

////////////////////////////////////////////////////////////////////////////////

void update_cars(AdjList* List) {
    No *proxNo, *atual;
    char flag;

    atual = List->cabeca;
    while(atual != NULL) {
        proxNo = atual->prox;
        if (timeToMove((Vehicle*) atual->v)) {
            flag = 0;
            update_car_movement((Vehicle*) atual->v);
            if(    (((Vehicle*) atual->v)->pos.y) < 0
                || (((Vehicle*) atual->v)->pos.y) >= SIZE_MAP
                || (((Vehicle*) atual->v)->pos.x) < 0
                || (((Vehicle*) atual->v)->pos.x) >= SIZE_MAP) {
                removeVehicleList(List,  ((Vehicle *) atual->v)->ID);
                flag = 1;
            }
        }
        if (flag == 0 && timeToSendPackage((Vehicle*) atual->v)) {
            dealSecToServer((Vehicle*) atual->v);
            dealEntToServer((Vehicle*) atual->v);
            dealConToServer((Vehicle*) atual->v);
        }
        atual = proxNo;
    }
}

////////////////////////////////////////////////////////////////////////////////

void update_car_movement(Vehicle* v) {
    switch (v->dir) {
        case North:
            (v->pos).y -= 1;
            break;
        case West:
            (v->pos).x -= 1;
            break;
        case South:
            (v->pos).y += 1;
            break;
        case East:
            (v->pos).x += 1;
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////

void change_car_speed(Vehicle* v, int speed) {
    v->car_speed = speed;
}

////////////////////////////////////////////////////////////////////////////////

void update_map(AdjList* List, char map[SIZE_MAP][SIZE_MAP]) {
    int i, j;
    for (i = 0; i < SIZE_MAP; i++) {
        for (j = 0; j < SIZE_MAP; j++) {
            if (i == (SIZE_MAP/2 - 1) || i == SIZE_MAP/2) {
                map[i][j] = '-';
            } else if (j == (SIZE_MAP/2 - 1) || j == SIZE_MAP/2) {
                map[i][j] = '-';
            } else {
                map[i][j] = 'x';
            }
        }
    }

    No* aux;
    for (aux = List->cabeca; aux != NULL; aux = aux->prox) {
        insert_v_in_map((Vehicle *) aux->v, map);
    }

}

////////////////////////////////////////////////////////////////////////////////

void insert_v_in_map(Vehicle* v, char map[SIZE_MAP][SIZE_MAP]) {
    if (v->type == Car) {
        map[(v->pos).y][(v->pos).x] = v->symbol;
    } else if (v->type == Truck) {
        if (v->dir == North) {
            map[(v->pos).y][(v->pos).x] = v->symbol;
            map[(v->pos).y+1][(v->pos).x] = v->symbol;
        } else if (v->dir == West ) {
            map[(v->pos).y][(v->pos).x] = v->symbol;
            map[(v->pos).y][(v->pos).x+1] = v->symbol;
        } else if (v->dir == South) {
            map[(v->pos).y][(v->pos).x] = v->symbol;
            map[(v->pos).y-1][(v->pos).x] = v->symbol;
        } else if (v->dir == East) {
            map[(v->pos).y][(v->pos).x] = v->symbol;
            map[(v->pos).y][(v->pos).x-1] = v->symbol;
        }
    } else if (v->type == DoubleTruck) {
        if (v->dir == North) {
            map[(v->pos).y][(v->pos).x] = v->symbol;
            map[(v->pos).y+1][(v->pos).x] = v->symbol;
            map[(v->pos).y+2][(v->pos).x] = v->symbol;
        } else if (v->dir == West ) {
            map[(v->pos).y][(v->pos).x] = v->symbol;
            map[(v->pos).y][(v->pos).x+1] = v->symbol;
            map[(v->pos).y][(v->pos).x+2] = v->symbol;
        } else if (v->dir == South) {
            map[(v->pos).y][(v->pos).x] = v->symbol;
            map[(v->pos).y-1][(v->pos).x] = v->symbol;
            map[(v->pos).y-2][(v->pos).x] = v->symbol;
        } else if (v->dir == East) {
            map[(v->pos).y][(v->pos).x] = v->symbol;
            map[(v->pos).y][(v->pos).x-1] = v->symbol;
            map[(v->pos).y][(v->pos).x-2] = v->symbol;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

int timeToSendPackage(Vehicle* v) {
    if ( (time_running - v->entry_time)% PACKAGE_INTERVAL == 0) {
        return 1;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

int timeToMove(Vehicle* v) {
    if ( (time_running - v->entry_time) % (int)(SPEED_INTERVAL/v->car_speed) == 0) {
        return 1;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

void dealSecToServer(Vehicle* v) {
#ifdef SEC_TCP
    SecPackageToClient* package = connectToTCPServer(v, Security);
#else
    SecPackageToClient* package = connectToUDPServer(v, Security);
#endif

#ifndef NCURSES_SIMULATE
    printf("Security Client:\n");
    printf("\tCar:    %d %d\n", v->ID, package->ID);
    printf("\tAction: %d %d\n", None, package->ac);
    printf("\tSpeed:  %d %d\n",v->car_speed, package->car_speed);
#endif

    if (package->ac == Increase || package->ac == Decrease) {
        change_car_speed(v, package->car_speed);
        commands++;
    } else if (package->ac == Ambulance) {
        ambulances++;
        v->symbol = 'a';
        // Chamar a ambulancia
    }
    free(package);
}

////////////////////////////////////////////////////////////////////////////////

void dealEntToServer(Vehicle* v) {
#ifdef ENT_TCP
    char* pkg = connectToTCPServer(v, Entertainment);
#else
    char* pkg = connectToUDPServer(v, Entertainment);
#endif

#ifndef NCURSES_SIMULATE
    printf("Entertainment Client:\n");
    printf("\tCar:    %d\n", v->ID);
    printf("\tMessage Received: %s\n", pkg);
#endif
    free(pkg);
}

////////////////////////////////////////////////////////////////////////////////

void dealConToServer(Vehicle* v) {
#ifdef CON_TCP
    char* pkg = connectToTCPServer(v, Confort);
#else
    char* pkg = connectToUDPServer(v, Confort);
#endif

#ifndef NCURSES_SIMULATE
    printf("Confort Client:\n");
    printf("\tCar:    %d\n", v->ID);
    printf("\tMessage Received: %s\n", pkg);
#endif
    free(pkg);
}

////////////////////////////////////////////////////////////////////////////////

void* connectToTCPServer(Vehicle* v, ConectionType contype) {
    struct hostent* host_address = NULL;
    struct sockaddr_in socket_address, socket_local;
    char* msg = calloc(PKG_ENT_SIZE, sizeof(char));
    int s, port, c;

    if (contype == Security) {
        port = SEC_PORT;
        host_address = gethostbyname(SEC_ADDRESS);
    } else if (contype == Entertainment) {
        port = ENT_PORT;
        host_address = gethostbyname(ENT_ADDRESS);
    } else if (contype == Confort) {
        port = CON_PORT;
        host_address = gethostbyname(CON_ADDRESS);
    }

    /* Translate the host name to IP*/
    if (host_address == NULL){
        printf("Error on gethostbyname\n");
        return NULL;
    }

    s = socket(AF_INET, SOCK_STREAM, 0);
    if ( s < 0 ) {
        printf("Problem occurred when creating a socket\n");
        return NULL;
    }

    /* Allocate the socket  and fills with the necessary info */
    bzero((char *)&socket_address, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);
    socket_address.sin_addr = *(struct in_addr*) host_address->h_addr_list[0];

    /* criação de socket ativo*/
    c = connect(s,(struct sockaddr*) &socket_address, sizeof(socket_address));
    if (c < 0) {
        printf("Problem occurred when connecting\n");
        return NULL;
    } else {
        // Conectou ao servidor
        unsigned int len = sizeof(socket_local);
        int i = getsockname(s, (struct sockaddr *) &socket_local, &len);

        if (i < 0){
            printf("Failed to obtaing information of the socket created\n");
        }
    }

    if (contype == Security) {
        SecPackageToServer* pkg = calloc(1, sizeof(SecPackageToServer));

        pkg->car_speed = v->car_speed;
        pkg->dir       = v->dir;
        pkg->ID        = v->ID;
        pkg->pos       = v->pos;
        pkg->length    = v->length;
        pkg->type      = v->type;
        pkg->time_sent = time_running;

        if (send(s, (const void*) pkg, sizeof(SecPackageToServer), 0) < 0) {
            printf("Problem sending message\n");
            return NULL;
        }

    } else if (contype == Entertainment) {
        char pkg[PKG_ENT_SIZE] = "\0";

        if (send(s, (const void*) pkg, PKG_ENT_SIZE, 0) < 0) {
            printf("Problem sending message\n");
            return NULL;
        }

    } else if (contype == Confort) {
        char pkg[PKG_CON_SIZE] = "\0";

        if (send(s, (const void*) pkg, PKG_ENT_SIZE, 0) < 0) {
            printf("Problem sending message\n");
            return NULL;
        }
    }

    if (recv(s, (void *) msg, MAX_LINE, 0) < 0) {
        printf("Could not receive any response\n");
        return NULL;
    }

    return msg;
}

////////////////////////////////////////////////////////////////////////////////

void* connectToUDPServer(Vehicle* v, ConectionType contype) {
    struct hostent *host_address = NULL;
    struct sockaddr_in socket_address;
    char* msg = calloc(PKG_ENT_SIZE, sizeof(char));
    int s, port, c;

    if (contype == Security) {
        port = SEC_PORT;
        host_address = gethostbyname(SEC_ADDRESS);
    } else if (contype == Entertainment) {
        port = ENT_PORT;
        host_address = gethostbyname(ENT_ADDRESS);
    } else if (contype == Confort) {
        port = CON_PORT;
        host_address = gethostbyname(CON_ADDRESS);
    }

    if (host_address == NULL){
        printf("Error on gethostbyname\n");
        return NULL;
    }

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if ( s < 0 ) {
        printf("Problem occurred when creating a socket\n");
        return NULL;
    }

    /* Allocate the socket  and fills with the necessary info */
    bzero((char *)&socket_address, sizeof(socket_address));
    //socket_address = (struct sockaddr_in*) calloc(1, sizeof(struct sockaddr_in*));
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);
    socket_address.sin_addr = *(struct in_addr*) host_address->h_addr_list[0];

    /* criação de socket ativo*/
    c = connect(s,(struct sockaddr*) &socket_address, sizeof(socket_address));
    if (c < 0) {
        printf("Problem occurred when connecting\n");
        return NULL;
    }

    int len = sizeof(socket_address);
    if (contype == Security) {
        SecPackageToServer* pkg = calloc(1, sizeof(SecPackageToServer));

        pkg->car_speed = v->car_speed;
        pkg->dir       = v->dir;
        pkg->ID        = v->ID;
        pkg->pos       = v->pos;
        pkg->length    = v->length;
        pkg->type      = v->type;
        pkg->time_sent = time_running;

        if (sendto(s, (const void*) pkg, sizeof(SecPackageToServer), 0, (const struct sockaddr*) &socket_address, len) < 0) {
            printf("Problem sending message\n");
            return NULL;
        }

    } else if (contype == Entertainment) {
        char pkg[PKG_ENT_SIZE] = "\0";

        if (sendto(s, (const void*) pkg, PKG_ENT_SIZE, 0, (const struct sockaddr*) &socket_address, len) < 0) {
            printf("Problem sending message\n");
            return NULL;
        }

    } else if (contype == Confort) {
        char pkg[PKG_CON_SIZE] = "\0";

        if (sendto(s, (const void*) pkg, PKG_CON_SIZE, 0, (const struct sockaddr*) &socket_address, len) < 0) {
            printf("Problem sending message\n");
            return NULL;
        }
    }

    recvfrom(s, (void*) msg, MAX_LINE, 0, (struct sockaddr*) &socket_address, (socklen_t *) &len);

    return (void*) msg;
}
