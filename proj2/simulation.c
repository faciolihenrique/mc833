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

////////////////////////////////////////////////////////////////////////////////

void simulate(AdjList* CarList) {
    if(time_running == 0){
        addVehicleList(CarList, create_vehicle(1, Car, 2, North));
        addVehicleList(CarList, create_vehicle(2, DoubleTruck, 2, East));
        addVehicleList(CarList, create_vehicle(3, Truck, 3, South));
        addVehicleList(CarList, create_vehicle(4, Truck, 1, West));
    }

    update_cars(CarList);

#ifdef NCURSES_SIMULATE
    update_map(CarList, CrossMap);
    printMap(CrossMap);
    if(isEmpty(CarList)){
        endwin();
    }
#endif

    ++time_running;
    if(isEmpty(CarList)){
        exit(0);
    }
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
    } else if(type == Truck) {
        v->length = SIZE_TRUCK;
    } else if(type == DoubleTruck){
        v->length = SIZE_DOUBLETRUCK;
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

void change_car_speed(Vehicle* v, int acceleration) {
    v->car_speed += acceleration;
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
        map[(v->pos).y][(v->pos).x] = 'c';
    } else if (v->type == Truck) {
        if (v->dir == North) {
            map[(v->pos).y][(v->pos).x] = 't';
            map[(v->pos).y+1][(v->pos).x] = 't';
        } else if (v->dir == West ) {
            map[(v->pos).y][(v->pos).x] = 't';
            map[(v->pos).y][(v->pos).x+1] = 't';
        } else if (v->dir == South) {
            map[(v->pos).y][(v->pos).x] = 't';
            map[(v->pos).y-1][(v->pos).x] = 't';
        } else if (v->dir == East) {
            map[(v->pos).y][(v->pos).x] = 't';
            map[(v->pos).y][(v->pos).x-1] = 't';
        }
    } else if (v->type == DoubleTruck) {
        if (v->dir == North) {
            map[(v->pos).y][(v->pos).x] = 'd';
            map[(v->pos).y+1][(v->pos).x] = 'd';
            map[(v->pos).y+2][(v->pos).x] = 'd';
        } else if (v->dir == West ) {
            map[(v->pos).y][(v->pos).x] = 'd';
            map[(v->pos).y][(v->pos).x+1] = 'd';
            map[(v->pos).y][(v->pos).x+2] = 'd';
        } else if (v->dir == South) {
            map[(v->pos).y][(v->pos).x] = 'd';
            map[(v->pos).y-1][(v->pos).x] = 'd';
            map[(v->pos).y-2][(v->pos).x] = 'd';
        } else if (v->dir == East) {
            map[(v->pos).y][(v->pos).x] = 'd';
            map[(v->pos).y][(v->pos).x-1] = 'd';
            map[(v->pos).y][(v->pos).x-2] = 'd';
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
    SecPackageToClient* package = connectToServer(v, Security);

    if (package->ac == Increase) {
        change_car_speed(v, package->car_speed);
    } else if (package->ac == Decrease) {
        change_car_speed(v, -package->car_speed);
    } else if (package->ac == Ambulance) {

    }
}

////////////////////////////////////////////////////////////////////////////////

void connectEntToServer(Vehicle* v) {

}
////////////////////////////////////////////////////////////////////////////////

void connectConToServer(Vehicle* v) {

}

////////////////////////////////////////////////////////////////////////////////

void* connectToServer(Vehicle* v, ConectionType contype) {
#ifdef UDP

#else
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

    /* Create a socket and check if its Ok
     * returns -1 if occurred an error
     * AF_INET = IPv4
     * SOCK_STREAM = TCP
     * 0 = Default
     */
    s = socket(AF_INET, SOCK_STREAM, 0);
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
    c = connect(s,(struct sockaddr*) &socket_address, sizeof(struct sockaddr_in));
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
#endif
    return 0;
}
