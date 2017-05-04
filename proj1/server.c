#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#define LISTEN_PORT 12345
#define MAX_PENDING 5
#define MAX_LINE 2048
#define ackMSGSize 700
//#define httpMSG "HTTP/1.1 200 OK\r\nCache-Control: no-cache, private\r\nContent-Length: 107\r\nContent-Type: text/html\r\nDate: Mon, 24 Nov 2014 10:21:21 GMT\r\n\r\nHello, World!\n"

int main(int argc, char * argv[])
{
	struct sockaddr_in socket_address, client_sa;
    char buf[MAX_LINE];
    unsigned int len;
    int s, port, b, l, newsoc;

    /* If no arg is passed, uses PORT 12345
     * else, uses the port passed
     */
    if (argc < 2){
        port = LISTEN_PORT;
        printf("Running Server on %d\n", port);
    } else {
        port = atoi(argv[1]);
        if (port == 0) {
            printf("Problem using the port passed\n");
            return -1;
        }
        printf("Running Server on %d\n", port);
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

    /* Criação da estrutura de dados de endereço */
    bzero((char *)&socket_address, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);
    socket_address.sin_addr.s_addr = INADDR_ANY;

    /* Associar socket ao descritor */
    b = bind(s, (struct sockaddr *) &socket_address, sizeof(socket_address));
    if (b < 0) {
        printf("Problem occurred when binding a socket\n");
        return -3;
    }

    /* Criar escuta do socket para aceitar conexões */
    l = listen(s, MAX_PENDING);
    if (l < 0) {
        printf("Problem accepting conections (listening)\n");
        return -3;
    }

	/* Aguarda/aceita conexão */
    len = sizeof(client_sa);
    newsoc = accept(s, (struct sockaddr *) &client_sa, &len);
    while(1){
        /* receber e imprimir texto na tela, enviar eco  */
        if(newsoc < 0){
            printf("Problem on creaing a new connection\n");
        }
        if( recv(newsoc, (void*) buf, MAX_LINE, 0) ) {
            printf("Message received\n");
            printf("From: %d\n", client_sa.sin_addr.s_addr);
            printf("Message:\n %s\n", buf);
        }

        send(newsoc, (const void*) buf, strlen(buf) + 1, 0);

        newsoc = accept(s, (struct sockaddr *) &client_sa, &len);
    }
    printf("Finishing Server\n");
    return 0;
}
