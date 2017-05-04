#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <netdb.h>

#define SERVER_PORT 12345
#define MAX_LINE 256

/* Receive two arguments
 * 1st : IP Address
 * 2nd : Port - If not second, uses default SERVER_PORT
 */
int main(int argc, char * argv[])
{
    struct hostent *host_address;
    struct sockaddr_in socket_address;
    char buf[MAX_LINE], msg[MAX_LINE];
    int s, port, c;

    /* Checking arguments */
    if (argc < 2){
        printf("Missing Host Address");
        return -1;
    } else if (argc < 3){
        port = SERVER_PORT;
    } else {
        port = atoi(argv[2]);
    }

    /* Translate the host name to IP*/
    host_address = gethostbyname(argv[1]);
    if (host_address == NULL){
        printf("Error on gethostbyname\n");
        return -3;
    }

    /* Create a socket and check if its Ok
     * returns -1 if occurred an error
     * AF_INET = IPv4
     * SOCK_STREAM = TCP
     * 0 = Default
     */
    s = socket(AF_INET, SOCK_STREAM, 0);
    if ( s < 0 ) {
        printf("Problem occurred when creating a socket\n");
        return -2;
    }

    /* Allocate the socket  and fills with the necessary info */
    bzero((char *)&socket_address, sizeof(socket_address));
    //socket_address = (struct sockaddr_in*) calloc(1, sizeof(struct sockaddr_in*));
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);
    socket_address.sin_addr = *(struct in_addr*) host_address->h_addr_list[0];

    /* criação de socket ativo*/
    c = connect(s,(struct sockaddr*) &socket_address, sizeof(struct sockaddr_in));
    if (c < 0) {
        printf("Problem occurred when connecting\n");
        return -4;
    }

    printf("Escreva a mensagem a ser enviada\n");
    bzero(buf,MAX_LINE);
    bzero(msg, MAX_LINE);
    fgets(buf,MAX_LINE,stdin);
    if(send(s, (const void*) buf, MAX_LINE, 0) < 0 ){
        printf("Problem sending message\n");
        return -5;
    }

    if (recv(s, (void *) msg, MAX_LINE, 0) < 0 ){
        printf("Could not receive any response\n");
        return -6;
    }
    printf("%s", msg);
}
