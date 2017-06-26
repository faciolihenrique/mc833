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

void simulate() {
    ++time;
    update_cars();
}

Vehicle create_vehicle(CarType type, Speed car_speed, Direction dir) {
    Vehicle v;
    int speed;

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
    speed = SPEED_MULTIPLIER * car_speed;
    if (speed >= 1 && speed <= SPEED_MULTIPLIER * MAX_SPEED) {
        v.car_speed = speed;
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
        case West:
            v.pos.x -= v.car_speed;
        case South:
            v.pos.y += v.car_speed;
        case East:
            v.pos.x += v.car_speed;
        default:
            break;
    }
}

void send_package() {

}
