/*~~~~~~ Functions ~~~~~~~*/
/* Creating the servers
 * each server creates a fork and starts a diferente server on diferente ports
 * media    10001
 * confort  10010
 * security 10100
 */
void create_router();
void create_media_server();
void create_security_server();
void create_confort_server();
