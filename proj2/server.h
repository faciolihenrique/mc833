#ifndef SERVER_H
#define SERVER_H

/*~~~~~~ Functions ~~~~~~~*/
/* Creating the servers.
 * Each server creates a fork and starts a diferente server on diferente ports
 * Entertainment 42000
 * Security      43000
 * Confort       44000
 */
void create_router();

/* Create a security server */
int create_security_server();

/* Create a entertainment server */
int create_entertainment_server();

/* Create a confort server */
int create_confort_server();

#endif
