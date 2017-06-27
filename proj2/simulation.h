#ifndef SIMULATION_H
#define SIMULATION_H

#include "main.h"

/* Functions to the simulation */
void simulate(AdjList* List);

/* Create a new vehicle */
Vehicle create_vehicle(int ID, CarType type, Speed car_speed, Direction dir);

/* Update the positions of all cars */
void update_cars(AdjList* List);

/* Update the car position based on its speed */
void update_car_movement(Vehicle v);

/* Change the speed of v based on the value of acceleration */
void change_car_speed(Vehicle v, int acceleration);

/* Send an update from the cars to the router */
void send_package();

#endif
