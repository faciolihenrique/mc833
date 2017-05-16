#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 12345
#define MAX_LINE 256

/* Receive two arguments
 * 1st : IP Address
 * 2nd : Port - If not second, uses default SERVER_PORT
 */
int main(int argc, char * argv[])
{
    struct hostent *host_address;
    struct sockaddr_in socket_address, socket_local;
    char buf[MAX_LINE], msg[MAX_LINE];
    int s, port, c;

    /* Checking arguments */
    if (argc < 2){
        printf("Missing Host Address\n");
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
    } else {
        // Conectou ao servidor
        unsigned int len = sizeof(socket_local);
        int i = getsockname(s, (struct sockaddr *) &socket_local, &len);

        if (i < 0){
            printf("Failed to obtaing information of the socket created\n");
        } else {
            printf("Connected to server using a new socket!\n");
            printf("Port: %d", ntohs(socket_local.sin_port));
            printf("\tTo: %s\n", inet_ntoa(socket_local.sin_addr));
        }
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
