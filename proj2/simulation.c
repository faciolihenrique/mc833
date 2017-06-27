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


unsigned long int time_running = 0;


char CrossMap[SIZE_MAP][SIZE_MAP];

void simulate(AdjList* CarList) {
    if(time_running == 0){
        addVehicleList(CarList, create_vehicle(1, Car, 1, North));
        //change_car_speed(&CarList->cabeca->v, 2);
        addVehicleList(CarList, create_vehicle(2, DoubleTruck, 1, East));
        addVehicleList(CarList, create_vehicle(3, Truck, 1, South));
        addVehicleList(CarList, create_vehicle(4, Truck, 1, West));
        update_map(CarList, CrossMap);
        printMap(CrossMap);
    }


    /* If the time mod SPEED_INTERVAL is 0, then its time to the cars to walk */
    if (time_running % SPEED_INTERVAL) {
        update_cars(CarList);
        update_map(CarList,CrossMap);
        printMap(CrossMap);
    }

    ++time_running;
}

////////////////////////////////////////////////////////////////////////////////

Vehicle* create_vehicle(int ID, CarType type, Speed car_speed, Direction dir) {
    Vehicle* v = malloc(sizeof(Vehicle));

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
    return v;
}

////////////////////////////////////////////////////////////////////////////////

void update_cars(AdjList* List) {
    No *proxNo, *atual;

    atual = List->cabeca;
    while(atual != NULL) {
        proxNo = atual->prox;
        update_car_movement((Vehicle*) atual->v);
        if(    (((Vehicle*) atual->v)->pos.y) < 0
            || (((Vehicle*) atual->v)->pos.y) >= SIZE_MAP
            || (((Vehicle*) atual->v)->pos.x) < 0
            || (((Vehicle*) atual->v)->pos.x) >= SIZE_MAP) {
            removeVehicleList(List,  ((Vehicle *) atual->v)->ID);
        }
        atual = proxNo;
    }
}

////////////////////////////////////////////////////////////////////////////////

void update_car_movement(Vehicle* v) {
    switch (v->dir) {
        case North:
            (v->pos).y -= v->car_speed;
            break;
        case West:
            (v->pos).x -= v->car_speed;
            break;
        case South:
            (v->pos).y += v->car_speed;
            break;
        case East:
            (v->pos).x += v->car_speed;
            break;
    }
}

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

void send_package(Vehicle v) {

}
