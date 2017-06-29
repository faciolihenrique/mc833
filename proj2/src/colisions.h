#ifndef COLISIONS_H
#define COLISIONS_H

#include "main.h"
#include "linked_list.h"

Action dealWithPackage(AdjList* List, SecPackageToServer* package, int* speed);

ServerCar* createNewServerCar(int ID, CarType type, int length, Position pos, Direction dir, Speed car_speed, Timestamp time_rec);

Action discoverAction(AdjList* List, ServerCar* car, int* speed);

int thereIsColision(ServerCar* car1, ServerCar* car2);

void removeOldPackages(AdjList* List);

int blocksToCross(Position pos, Direction dir);

void updateSpeed(Speed newSpeed, ServerCar* car);

#endif
