/* 2017
 * Projeto 2 - mc833 - Laboratório de Redes
 * colisions.c
 *
 * Henrique Noronha Facioli - 157986
 * Thiago Silva de Farias - 148077
 */

#include "main.h"
#include "colisions.h"

Action dealWithPackage(AdjList* List, SecPackageToServer* package) {
    if(isInServerCarList(List, package->ID)) {
        /*Atualizar dados do carro*/
        //Pensar em como atualizar.
        return Continue;
    }
    else {
        /*Criamos um novo carro para o servidor e o adicionamos a lista */
        ServerCar* s;
        s = createNewServerCar(package->ID, package->type, package->length, package->pos, package->dir, package->car_speed, package->time_sent);
        addServerCarList(List, s);
    }
    //Pensar no que retornar.
    return 0;
}

ServerCar* createNewServerCar(int ID, CarType type, int length, Position pos, Direction dir, Speed car_speed, Timestamp time_rec) {
    ServerCar* s = calloc(1,sizeof(ServerCar));

    s->ID = ID;
    s->type = type;
    s->length = length;
    s->pos = pos;
    s->dir = dir;
    s->car_speed = car_speed;
    s->time_rec = time_rec;
    s->estimated_time_in = 0;
    s->estimated_time_middle = 0;
    s->estimated_time_out = 0;
    s->destroy = 0;

    return s;
}

Action discoverAction(AdjList* List, ServerCar* car) {
    No *atual = List->cabeca;
    int original_speed = car->car_speed;
    int increase_decrease = 0;
    int cont = 1;

    while(atual != NULL) {
        if(thereIsColision(car, (ServerCar*) atual->v) && increase_decrease == 0) {
            cont = 0;
            if(car->car_speed == MAX_SPEED){
                increase_decrease = 1;
                car->car_speed = original_speed;
            }
            else {
                car->car_speed++;
            }
            atual = List->cabeca;
        }
        if(thereIsColision(car, (ServerCar*) atual->v) && increase_decrease == 1) {
            cont = 0;
            if(car->car_speed == 1){
                return Ambulance;
            }
            else {
                car->car_speed--;
            }
            atual = List->cabeca;
        }
        atual = atual->prox;
    }
    if(cont) {
        return Continue;
    }
    else {
        if(increase_decrease) {
            return Decrease;
        }
        else {
            return Increase;
        }
    }
}

int thereIsColision(ServerCar* car1, ServerCar* car2) {
    if(car1->dir == North && car2->dir == East) {
        /* Car 1 exits cross before Car 2 enters it */
        if(car1->estimated_time_middle < car2->estimated_time_middle) {
            return 0;
        }
        /* Car 2 exits cross before Car 1 enters it */
        else if(car2->estimated_time_out < car1->estimated_time_in) {
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(car1->dir == North && car2->dir == West) {
        /* Car 1 exits cross before Car 2 enters it */
        if(car1->estimated_time_out < car2->estimated_time_in) {
            return 0;
        }
        /* Car 2 exits cross before Car 1 enters it */
        else if(car2->estimated_time_middle < car1->estimated_time_middle) {
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(car1->dir == South && car2->dir == East) {
        /* Car 1 exits cross before Car 2 enters it */
        if(car1->estimated_time_out < car2->estimated_time_in) {
            return 0;
        }
        /* Car 2 exits cross before Car 1 enters it */
        else if(car2->estimated_time_middle < car1->estimated_time_middle) {
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(car1->dir == South && car2->dir == West) {
        /* Car 1 enters and exits cross before Car 2 enters it */
        if(car1->estimated_time_middle < car2->estimated_time_middle) {
            return 0;
        }
        /* Car 2 enters and exits cross before Car 1 enters it */
        else if(car2->estimated_time_out < car1->estimated_time_in) {
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(car1->dir == East && car2->dir == North) {
        /* Car 2 exits cross before Car 1 enters it */
        if(car2->estimated_time_middle < car1->estimated_time_middle) {
            return 0;
        }
        /* Car 1 exits cross before Car 2 enters it */
        else if(car1->estimated_time_out < car2->estimated_time_in) {
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(car1->dir == West && car2->dir == North) {
        /* Car 2 exits cross before Car 1 enters it */
        if(car2->estimated_time_out < car1->estimated_time_in) {
            return 0;
        }
        /* Car 1 exits cross before Car 2 enters it */
        else if(car1->estimated_time_middle < car2->estimated_time_middle) {
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(car1->dir == East && car2->dir == South) {
        /* Car 2 exits cross before Car 1 enters it */
        if(car2->estimated_time_out < car1->estimated_time_in) {
            return 0;
        }
        /* Car 1 exits cross before Car 2 enters it */
        else if(car1->estimated_time_middle < car2->estimated_time_middle) {
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(car1->dir == West && car2->dir == South) {
        /* Car 2 enters and exits cross before Car 1 enters it */
        if(car2->estimated_time_middle < car1->estimated_time_middle) {
            return 0;
        }
        /* Car 1 enters and exits cross before Car 2 enters it */
        else if(car1->estimated_time_out < car2->estimated_time_in) {
            return 0;
        }
        else{
            return 1;
        }
    }
    /* Both cars are parallel */
    else {
        return 0;
    }
}
