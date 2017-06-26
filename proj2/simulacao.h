#ifndef SIMULACAO_H
#define SIMULACAO_H

#include "main.h"
/* Functions to the simulation */
void simulate(Vehicle vehicles[], int n);
Vehicle create_vehicle(CarType type, Speed car_speed, Direction dir);
void update_cars(Vehicle vehicles[], int n);
void update_car_movement(Vehicle v);
void change_car_speed(Vehicle v, int acceleration);
void send_package();

#endif
