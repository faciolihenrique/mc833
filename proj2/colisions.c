/* 2017
 * Projeto 2 - mc833 - Laboratório de Redes
 * colisions.c
 *
 * Henrique Noronha Facioli - 157986
 * Thiago Silva de Farias - 148077
 */

#include "main.h"
#include "colisions.h"

extern unsigned long int time_running;

int using = 0;

////////////////////////////////////////////////////////////////////////////////

Action dealWithPackage(AdjList* List, SecPackageToServer* package, int* speed) {
    removeOldPackages(List);

    printf("dealWithPackage\n\tspeed:%d\n\tdir:%d\n\tID:%d\n\tlenght:%d\n\ttime_sent:%ld\n\ttype:%d\n", package->car_speed, package->dir, package->ID, package->length, package->time_sent, package->type);

    if(isInServerCarList(List, package->ID)) {
        printf("Estou achando esse id na lista\n");
        *speed = package->car_speed;
        return Continue;
    }
    else {
        printf("Não estou achando esse id na lista\n");
        /*Criamos um novo carro para o servidor e o adicionamos a lista */
        ServerCar* s;
        s = createNewServerCar(package->ID, package->type, package->length, package->pos, package->dir, package->car_speed, package->time_sent);
        addServerCarList(List, s);
        return discoverAction(List, s, speed);
    }
}

////////////////////////////////////////////////////////////////////////////////

ServerCar* createNewServerCar(int ID, CarType type, int length, Position pos, Direction dir, Speed car_speed, Timestamp time_rec) {
    ServerCar* s = calloc(1,sizeof(ServerCar));
    int number_blocks;

    s->ID = ID;
    s->type = type;
    s->length = length;
    s->pos = pos;
    s->dir = dir;
    s->car_speed = car_speed;
    s->time_rec = time_rec;
    number_blocks = blocksToCross(pos, dir);
    s->estimated_time_in1 = time_rec + (number_blocks*SPEED_INTERVAL)/car_speed;
    s->estimated_time_out1 = time_rec + ((number_blocks+length)*SPEED_INTERVAL)/car_speed;
    s->estimated_time_in2 = time_rec + ((number_blocks+1)*SPEED_INTERVAL)/car_speed;
    s->estimated_time_out2 = time_rec + ((number_blocks+length+1)*SPEED_INTERVAL)/car_speed;
    s->destroy = time_rec + ((number_blocks+(SIZE_MAP/2)+1)*SPEED_INTERVAL)/car_speed;

    printf("\tin1: %ld\n\tin2: %ld \n\tout1: %ld \n\tout2: %ld\n\tdestroy: %ld\n",s->estimated_time_in1, s->estimated_time_in2, s->estimated_time_out1,s->estimated_time_out2,s->destroy );

    return s;
}

////////////////////////////////////////////////////////////////////////////////

Action discoverAction(AdjList* List, ServerCar* car, int* speed) {
    No *atual = List->cabeca;
    int original_speed = car->car_speed;
    int increase_decrease = 0;
    int cont = 1;
    printf("Descobrindo a Ação!\n");

    while(atual != NULL) {
        if (thereIsColision(car, (ServerCar*) atual->v)) {
            if(increase_decrease == 0) {
                printf("Detectou colisao, aumentando velocidade de %d\n", car->ID);
                cont = 0;
                if(car->car_speed == MAX_SPEED){
                    printf("Já tentou aumentar ao máximo.\n");
                    increase_decrease = 1;
                    *speed = original_speed;
                    car->car_speed = original_speed;
                } else {
                    updateSpeed(car->car_speed+1, car);
                }
                atual = List->cabeca;
            } else {
                printf("Detectou colisao, diminuindo velocidade de %d\n", car->ID);
                cont = 0;
                if(car->car_speed == 1){
                    printf("Já tentou diminuir ao minimo.\n");
                    car->car_speed = original_speed;
                    *speed = original_speed;
                    return Ambulance;
                }
                else {
                    updateSpeed(car->car_speed-1, car);
                }
                atual = List->cabeca;
            }
        } else {
            printf("Não há colisão entre %d %d\n", car->ID, ((ServerCar*) atual->v)->ID);
            atual = atual->prox;
        }
    }
    if(cont) {
        *speed = original_speed;
        return Continue;
    }
    else {
        if(increase_decrease) {
            *speed = car->car_speed;
            return Decrease;
        }
        else {
            *speed = car->car_speed;
            return Increase;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

int thereIsColision(ServerCar* car1, ServerCar* car2) {
    if(car1->dir == North && car2->dir == East) {
        /* Car 1 exits cross before Car 2 enters it */
        if(car1->estimated_time_out1 < car2->estimated_time_in2) {
            return 0;
        }
        /* Car 2 exits cross before Car 1 enters it */
        else if(car2->estimated_time_out2 < car1->estimated_time_in1) {
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(car1->dir == North && car2->dir == West) {
        printf("Entrou aqui no car1 North\n");
        /* Car 1 exits cross before Car 2 enters it */
        if(car1->estimated_time_out2 < car2->estimated_time_in1) {
            return 0;
        }
        /* Car 2 exits cross before Car 1 enters it */
        else if(car2->estimated_time_out1 < car1->estimated_time_in2) {
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(car1->dir == South && car2->dir == East) {
        /* Car 1 exits cross before Car 2 enters it */
        if(car1->estimated_time_out2 < car2->estimated_time_in1) {
            return 0;
        }
        /* Car 2 exits cross before Car 1 enters it */
        else if(car2->estimated_time_out1 < car1->estimated_time_in2) {
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(car1->dir == South && car2->dir == West) {
        /* Car 1 exits cross before Car 2 enters it */
        if(car1->estimated_time_out1 < car2->estimated_time_in2) {
            return 0;
        }
        /* Car 2 exits cross before Car 1 enters it */
        else if(car2->estimated_time_out2 < car1->estimated_time_in1) {
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(car1->dir == East && car2->dir == North) {
        /* Car 2 exits cross before Car 1 enters it */
        if(car2->estimated_time_out1 < car1->estimated_time_in2) {
            return 0;
        }
        /* Car 1 exits cross before Car 2 enters it */
        else if(car1->estimated_time_out2 < car2->estimated_time_in1) {
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(car1->dir == West && car2->dir == North) {
        printf("Entrou aqui no car1 West\n");
        /* Car 2 exits cross before Car 1 enters it */
        if(car2->estimated_time_out2 < car1->estimated_time_in1) {
            return 0;
        }
        /* Car 1 exits cross before Car 2 enters it */
        else if(car1->estimated_time_out1 < car2->estimated_time_in2) {
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(car1->dir == East && car2->dir == South) {
        /* Car 2 exits cross before Car 1 enters it */
        if(car2->estimated_time_out2 < car1->estimated_time_in1) {
            return 0;
        }
        /* Car 1 exits cross before Car 2 enters it */
        else if(car1->estimated_time_out1 < car2->estimated_time_in2) {
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(car1->dir == West && car2->dir == South) {
        /* Car 2 exits cross before Car 1 enters it */
        if(car2->estimated_time_out1 < car1->estimated_time_in2) {
            return 0;
        }
        /* Car 1 exits cross before Car 2 enters it */
        else if(car1->estimated_time_out2 < car2->estimated_time_in1) {
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

////////////////////////////////////////////////////////////////////////////////

void removeOldPackages(AdjList* List){
    No *atual = List->cabeca;
    while(atual != NULL) {
        if(((ServerCar*) atual->v)->destroy <= time_running) {
            printf("Removendo %d\n\tDestroy: %ld\n\ttime_runnig: %ld\n",((ServerCar*) atual->v)->ID, ((ServerCar*) atual->v)->destroy ,time_running);
            removeServerCarList(List, ((ServerCar*) atual->v)->ID);
        }
        atual = atual->prox;
    }
}

////////////////////////////////////////////////////////////////////////////////

int blocksToCross(Position pos, Direction dir) {
    int number_blocks;
    switch (dir) {
        case North:
            number_blocks = pos.y - SIZE_MAP/2;
            break;
        case West:
            number_blocks = pos.x - SIZE_MAP/2;
            break;
        case South:
            number_blocks = (SIZE_MAP/2 - 1) - pos.y;
            break;
        case East:
            number_blocks = (SIZE_MAP/2 - 1) - pos.x;
            break;
    }
    return number_blocks;
}

////////////////////////////////////////////////////////////////////////////////

void updateSpeed(Speed newSpeed, ServerCar* car) {
    car->car_speed = newSpeed;

    int number_blocks = blocksToCross(car->pos, car->dir);

    car->estimated_time_in1 = car->time_rec + (number_blocks*SPEED_INTERVAL)/car->car_speed;
    car->estimated_time_out1 = car->time_rec + ((number_blocks+car->length)*SPEED_INTERVAL)/car->car_speed;
    car->estimated_time_in2 = car->time_rec + ((number_blocks+1)*SPEED_INTERVAL)/car->car_speed;
    car->estimated_time_out2 = car->time_rec + ((number_blocks+car->length+1)*SPEED_INTERVAL)/car->car_speed;
    car->destroy = car->time_rec + ((number_blocks+(SIZE_MAP/2)+1)*SPEED_INTERVAL)/car->car_speed;

    printf("New timestamps para %d\n", car->ID);
    printf("\tin1: %ld\n\tin2: %ld \n\tout1: %ld \n\tout2: %ld\n\tdestroy: %ld\n",car->estimated_time_in1, car->estimated_time_in2, car->estimated_time_out1,car->estimated_time_out2 , car->destroy );
}
