#ifndef SERVER_H
#define SERVER_H

/*~~~~~~ Functions ~~~~~~~*/
/* Creating the servers
 * each server creates a fork and starts a diferente server on diferente ports
 * media    10001
 * confort  10010
 * security 10100
 */
void create_router();

/* Create a security server */
int create_security_server();

/* Create a media server */
int create_media_server();

/* Create a confort server */
int create_confort_server();

#endif
