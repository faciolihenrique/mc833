#ifndef SERVER_H
#define SERVER_H

#include "main.h"
#include "linked_list.h"

/*~~~~~~ Functions ~~~~~~~*/
/* Creating the servers.
 * Each server creates a fork and starts a different server on different ports
 * Entertainment 42000
 * Security      43000
 * Confort       44000
 */
void create_router();

/* Create a security server
 * When receiveing a message from a car, it gets the infos sent from the car
 * and calculates if there will be a colision. If so it tries to increase from 1
 * and checks if there will be a colision. If v max is reached and will have a
 * collision, then it starts slowing and if reaches 1 and a colision is detected
 * then we call the ambulance.
 * If the collision is avoided, the car is then inserted on a list with the time
 * it need to be removed from the list (after it passes the cross) and the
 * server always runs through the list checking if there will be any of them
 * removed
 */
int create_security_server();

/* Create a entertainment server
 * Receiving this package always send a response tripled sized
 */
int create_entertainment_server();

/* Create a confort server
 * Receiving this package always send a response doubled sized
 */
int create_confort_server();

#endif
