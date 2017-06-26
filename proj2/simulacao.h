#include "main.h"

/* Functions to the simulation */
void simulate();
Vehicle create_vehicle(CarType type, Speed car_speed, Direction dir);
void update_cars(Vehicle vehicles[], int n);
void update_car_movement(Vehicle vehicle);
void send_package();
