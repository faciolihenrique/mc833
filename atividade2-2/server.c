#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define LISTEN_PORT 12345
#define MAX_PENDING 5
#define MAX_LINE 2048
#define ackMSGSize 700

int main(int argc, char * argv[])
{
	struct sockaddr_in socket_address, client_helper;
    char buf[MAX_LINE];
    unsigned int len;
    int s, port, b, l, newsoc, maxfd, sockfd, cliente_num, nready, i, clientes[FD_SETSIZE];
    fd_set todos_fds, novo_set;

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


    maxfd = s;
    cliente_num = -1;
    for (i = 0; i < FD_SETSIZE; i++)
        clientes[i] = -1;

    FD_ZERO(&todos_fds);
    FD_SET(s, &todos_fds);

    while(1){
        novo_set = todos_fds;
        nready = select(maxfd+1, &novo_set, NULL, NULL, NULL);
        if(nready < 0) {
            printf("Failed to use select\n");
            return -4;
        }

        if(FD_ISSET(s, &novo_set)) {
            len = sizeof(socket_address);
            newsoc = accept(s, (struct sockaddr *)&socket_address, &len);

            if(newsoc < 0) {
                printf("Problem on creaing a new connection\n");
                return -5;
            }
            for (i = 0; i < FD_SETSIZE; i++) {
                if (clientes[i] < 0) {
                    clientes[i] = newsoc; 	//guarda descritor
                    break;
                }
            }
            if (i == FD_SETSIZE) {
                printf("Maximum number of clients already established\n");
             		return -6;
            }

            FD_SET(newsoc, &todos_fds);		// adiciona novo descritor ao conjunto
            if (newsoc > maxfd)
                maxfd = newsoc;			// para o select
            if (i > cliente_num)
                cliente_num = i;		// Ã­ndice mÃ¡ximo no vetor clientes[]
            if (--nready <= 0)
                continue;			// nÃ£o existem mais descritores para serem lidos
        }

        for (i = 0; i <= cliente_num; i++) {	// verificar se hÃ¡ dados em todos os clientes
            if ( (sockfd = clientes[i]) < 0)
                continue;
            if (FD_ISSET(sockfd, &novo_set)) {
                if ( (len = recv(sockfd, buf, sizeof(buf), 0)) == 0) {
                    //conexÃ£o encerrada pelo cliente
                    close(sockfd);
                    FD_CLR(sockfd, &todos_fds);
                    clientes[i] = -1;
                } else {
                    int t = getpeername(newsoc, (struct sockaddr *) &client_helper, &len);
                    if (t < 0){
                        printf("Failed to estabilsh connect\n");
                    } else {
                        printf("New client connected!\n");
                        printf("Port: %d", ntohs(client_helper.sin_port));
                        printf("\tFrom: %s\n", inet_ntoa(client_helper.sin_addr));

                        if( recv(newsoc, (void*) buf, MAX_LINE, 0) ) {
                            printf("Message received\n");
                            printf("Port: %d", ntohs(client_helper.sin_port));
                            printf("  From: %s\n", inet_ntoa(client_helper.sin_addr));
                            printf("Message:\n %s\n", buf);
                        }
                        send(newsoc, (const void*) buf, strlen(buf) + 1, 0);
                    }
                }
                if (--nready <= 0)
                    break;				// nÃ£o existem mais descritores para serem lidos
            }
        }
    }
}
