/* 2017
 * Projeto 2 - mc833 - Laboratório de Redes
 * main.c
 *
 * Henrique Noronha Facioli - 157986
 * Thiago Silva de Farias - 148077
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "main.h"
#include "simulacao.h"

unsigned long int time = 0;

void simulate(Vehicle vehicles[], int n) {
    ++time;
    update_cars(vehicles, n);
}

Vehicle create_vehicle(CarType type, Speed car_speed, Direction dir) {
    Vehicle v;

    // CarType.
    v.type = type;
    // Length according to Type.
    if(type == Car) {
        v.length = SIZE_CAR;
    } else if(type == Truck) {
        v.length = SIZE_TRUCK;
    } else if(type == DoubleTruck){
        v.length = SIZE_DOUBLETRUCK;
    }
    // Speed.
    if (car_speed >= 1 && car_speed <= MAX_SPEED) {
        v.car_speed = car_speed;
    }
    // Direction.
    v.dir = dir;
    // Initial Position according to Direction.
    if(dir == North) {
        v.pos.y = (SIZE_MAP - 1) - v.length;
        v.pos.x = SIZE_MAP/2;
    } else if(dir == West) {
        v.pos.y = (SIZE_MAP/2) - 1;
        v.pos.x = (SIZE_MAP - 1) - v.length;
    } else if(dir == South) {
        v.pos.y = v.length;
        v.pos.x = (SIZE_MAP/2) - 1;
    } else if(dir == East) {
        v.pos.y = SIZE_MAP/2;
        v.pos.x = v.length;
    }
    return v;
}

void update_cars(Vehicle vehicles[], int n) {

}

void update_car_movement(Vehicle v) {
    switch (v.dir) {
        case North:
            v.pos.y -= v.car_speed;
            break;
        case West:
            v.pos.x -= v.car_speed;
            break;
        case South:
            v.pos.y += v.car_speed;
            break;
        case East:
            v.pos.x += v.car_speed;
            break;
    }
}

void change_car_speed(Vehicle v, int acceleration) {
    v.car_speed += acceleration;
}

void send_package() {

}
