#ifndef COLISIONS_H
#define COLISIONS_H

#include "main.h"
#include "linked_list.h"

Action dealWithPackage(AdjList* List, SecPackageToServer* package);

ServerCar* createNewServerCar(int ID, CarType type, int length, Position pos, Direction dir, Speed car_speed, Timestamp time_rec);

Action discoverAction(AdjList* List, ServerCar* car);

int thereIsColision(ServerCar* car1, ServerCar* car2);

#endif
