#ifndef SIMULATION_H
#define SIMULATION_H

#include "main.h"

/* Functions to the simulation */
void simulate(Vehicle vehicles[], int n);

/* Create a new vehicle */
Vehicle create_vehicle(CarType type, Speed car_speed, Direction dir);

/* */
void update_cars(Vehicle vehicles[], int n);

/* Update the car position based on its speed*/
void update_car_movement(Vehicle v);

/* Change the speed of v of acceleration */
void change_car_speed(Vehicle v, int acceleration);

/* Send an update from the cars to the router */
void send_package();

#endif
