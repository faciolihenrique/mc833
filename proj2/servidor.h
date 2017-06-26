/*~~~~~~ Functions ~~~~~~~*/
/* Creating the servers
 * each server creates a fork and starts a diferente server on diferente ports
 * media    10001
 * confort  10010
 * security 10100
 */

#ifndef SERVIDOR_H
#define SERVIDOR_H

void create_router();
int create_security_server();
int create_media_server();
int create_confort_server();

#endif
