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
        v.length = 1;
    } else if(type == Truck) {
        v.length = 2;
    } else if(type == DoubleTruck){
        v.length = 3;
    }
    // Speed.
    speed = SPEED_MULTIPLIER * car_speed;
    if (speed >= 1 && speed <= MAX_SPEED) {
        v.car_speed = speed;
    }
    // Direction.
    v.dir = dir;
    // Initial Position according to Direction.
    if(dir == North) {
        v.pos.x = (SIZE_MAP - 1) - v.length;
        v.pos.y = SIZE_MAP/2;
    } else if(dir == West) {
        v.pos.x = (SIZE_MAP/2) - 1;
        v.pos.y = (SIZE_MAP - 1) - v.length;
    } else if(dir == South) {
        v.pos.x = v.length;
        v.pos.y = (SIZE_MAP/2) - 1;
    } else if(dir == East) {
        v.pos.x = SIZE_MAP/2;
        v.pos.y = v.length;
    }
    return v;
}

void update_cars(Vehicle vehicles[], int n) {

}

void update_car_movement(Vehicle vehicle) {

}

void send_package() {

}
