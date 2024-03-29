#ifndef SIMULATION_H
#define SIMULATION_H

#include "main.h"
#include "linked_list.h"

/* Functions to the simulation */
int simulate(AdjList* CarList);

/* Create a new vehicle */
Vehicle* create_vehicle(int ID, CarType type, Speed car_speed, Direction dir);

/* Update the positions of all cars */
void update_cars(AdjList* List);

/* Update the car position based on its speed */
void update_car_movement(Vehicle* v);

/* Change the speed of v based on the value received */
void change_car_speed(Vehicle* v, int speed);

/* Update and returns a matrix representing the simulation */
void update_map(AdjList* List, char matrix[SIZE_MAP][SIZE_MAP]);

/* Insert the vehicle v car on the map */
void insert_v_in_map(Vehicle* v, char map[SIZE_MAP][SIZE_MAP]);

/* Send an update from the cars to the router specified */
void* connectToTCPServer(Vehicle* v, ConectionType contype);

void* connectToUDPServer(Vehicle* v, ConectionType contype);

/* Check if its time to move the car */
int timeToMove(Vehicle* v);

/* Check if its time to the car send the package */
int timeToSendPackage(Vehicle* v);

/* Connect to sec server and do what is needed */
void dealSecToServer(Vehicle* v);

void dealEntToServer(Vehicle* v);

void dealConToServer(Vehicle* v);

#endif
