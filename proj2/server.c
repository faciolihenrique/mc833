/* 2017
 * Projeto 2 - mc833 - Laboratório de Redes
 * server.c
 *
 * Henrique Noronha Facioli - 157986
 * Thiago Silva de Farias - 148077
 */

#include "main.h"
#include "server.h"

extern unsigned long int time_running;

////////////////////////////////////////////////////////////////////////////////

void create_router() {
    if (fork()) {

    } else {
        if (fork()) {
            if (fork()) {
                create_security_server();
                printf("Saiu Seguranca\n");
            } else {
                create_entertainment_server();
                printf("Saiu Entreterimento\n");
            }
        } else {
            create_confort_server();
            printf("Saiu Conforto\n");
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

#ifdef UDP

int create_security_server() {
    return 1;
}
int create_entertainment_server() {
    return 1;
}
int create_confort_server() {
    return 1;
}

#else

////////////////////////////////////////////////////////////////////////////////

int create_security_server() {
    struct sockaddr_in socket_address, client_sa, client_helper;
    char* buf = calloc(PKG_ENT_SIZE, sizeof(char));
    unsigned int len;
    int s, port, b, l, newsoc;

    port = SEC_PORT;
    printf("Starting Security Server on %d\n", port);

    /* Create a socket and check if its Ok
     * returns -1 if occurred an error
     * AF_INET = IPv4
     * SOCK_STREAM = TCP
     * 0 = Default
     */
    s = socket(AF_INET, SOCK_STREAM, 0);
    if ( s < 0 ) {
        printf("Security: Problem occurred when creating a socket\n");
        exit(0);
    }

    /* Criação da estrutura de dados de endereço */
    bzero((char *)&socket_address, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);
    socket_address.sin_addr.s_addr = INADDR_ANY;

    /* Associar socket ao descritor */
    b = bind(s, (struct sockaddr *) &socket_address, sizeof(socket_address));
    if (b < 0) {
        printf("Security: Problem occurred when binding a socket\n");
        exit(0);
    }

    /* Criar escuta do socket para aceitar conexões */
    l = listen(s, MAX_PENDING);
    if (l < 0) {
        printf("Security: Problem accepting conections (listening)\n");
        exit(0);
    }

    /* Aguarda/aceita conexão */
    len = sizeof(client_sa);

    while(1){
        newsoc = accept(s, (struct sockaddr *) &client_sa, &len);

        if(newsoc < 0){
            printf("Security: Problem on creaing a new connection\n");
        }

        int pid = fork();
        /* pid = 0 => Processo pai
         * pid > 0 => Processo filho
         * pid < 0 => erro
         */
        if (pid < 0){
            printf("Security: Failed to create a new fork\n");
            close(newsoc);
        } else if (pid > 0) {
            int i = getpeername(newsoc, (struct sockaddr *) &client_helper, &len);

            if (i < 0){
                printf("Security: Failed to estabilsh connect\n");
            } else {
#ifndef NCURSES_SIMULATE
                printf("Security: New client connected!\n");
                printf("Security: Port: %d", ntohs(client_helper.sin_port));
                printf("\tFrom: %s\n", inet_ntoa(client_helper.sin_addr));

                if( recv(newsoc, (void*) buf, sizeof(SecPackageToServer), 0) ) {
                    printf("Security: Message received");
                    printf("\tPort: %d", ntohs(client_helper.sin_port));
                    printf("\tFrom: %d\n", ((SecPackageToServer*) buf)->ID);
                }
#else
                recv(newsoc, (void*) buf, sizeof(SecPackageToServer), 0);
#endif
                SecPackageToClient* rsp = calloc(1, sizeof(SecPackageToClient));

                rsp->ID = ((SecPackageToServer*) buf)->ID;
                rsp->ac = Continue;
                rsp->car_speed = ((SecPackageToServer*) buf)->car_speed;

                send(newsoc, (const void*) rsp, sizeof(SecPackageToServer), 0);
            }
        }
    }
    printf("Finishing Server\n");
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

int create_entertainment_server() {
    struct sockaddr_in socket_address, client_sa, client_helper;
    char buf[MAX_LINE];
    unsigned int len;
    int s, port, b, l, newsoc;

    port = ENT_PORT;
    printf("Starting Entertainment Server on %d\n", port);

    /* Create a socket and check if its Ok
     * returns -1 if occurred an error
     * AF_INET = IPv4
     * SOCK_STREAM = TCP
     * 0 = Default
     */
    s = socket(AF_INET, SOCK_STREAM, 0);
    if ( s < 0 ) {
        printf("Entertainment: Problem occurred when creating a socket\n");
        exit(0);
    }

    /* Criação da estrutura de dados de endereço */
    bzero((char *)&socket_address, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);
    socket_address.sin_addr.s_addr = INADDR_ANY;

    /* Associar socket ao descritor */
    b = bind(s, (struct sockaddr *) &socket_address, sizeof(socket_address));
    if (b < 0) {
        printf("Entertainment: Problem occurred when binding a socket\n");
        exit(0);
    }

    /* Criar escuta do socket para aceitar conexões */
    l = listen(s, MAX_PENDING);
    if (l < 0) {
        printf("Entertainment: Problem accepting conections (listening)\n");
        exit(0);
    }

    /* Aguarda/aceita conexão */
    len = sizeof(client_sa);

    while(1){
        newsoc = accept(s, (struct sockaddr *) &client_sa, &len);

        if(newsoc < 0){
            printf("Entertainment: Problem on creaing a new connection\n");
        }

        int pid = fork();
        /* pid = 0 => Processo pai
         * pid > 0 => Processo filho
         * pid < 0 => erro
         */
        if (pid < 0){
            printf("Entertainment: Failed to create a new fork\n");
            close(newsoc);
        } else if (pid > 0) {
            int i = getpeername(newsoc, (struct sockaddr *) &client_helper, &len);

            if (i < 0){
                printf("Entertainment: Failed to estabilsh connect\n");
            } else {
                printf("Entertainment: New client connected!\n");
                printf("Entertainment: Port: %d", ntohs(client_helper.sin_port));
                printf("\tFrom: %s\n", inet_ntoa(client_helper.sin_addr));

                if( recv(newsoc, (void*) buf, MAX_LINE, 0) ) {
                    printf("Entertainment: Message received\n");
                    printf("Entertainment: Port: %d", ntohs(client_helper.sin_port));
                    printf("Entertainment:   From: %s\n", inet_ntoa(client_helper.sin_addr));
                    printf("Entertainment: Message:\n %s\n", buf);
                }
                send(newsoc, (const void*) buf, strlen(buf) + 1, 0);
            }
        }
    }
    printf("Finishing Server\n");
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

int create_confort_server() {
    struct sockaddr_in socket_address, client_sa, client_helper;
    char buf[MAX_LINE];
    unsigned int len;
    int s, port, b, l, newsoc;

    port = CON_PORT;
    printf("Starting Confort Server on %d\n", port);

    /* Create a socket and check if its Ok
     * returns -1 if occurred an error
     * AF_INET = IPv4
     * SOCK_STREAM = TCP
     * 0 = Default
     */
    s = socket(AF_INET, SOCK_STREAM, 0);
    if ( s < 0 ) {
        printf("Confort: Problem occurred when creating a socket\n");
        exit(0);
    }

    /* Criação da estrutura de dados de endereço */
    bzero((char *)&socket_address, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);
    socket_address.sin_addr.s_addr = INADDR_ANY;

    /* Associar socket ao descritor */
    b = bind(s, (struct sockaddr *) &socket_address, sizeof(socket_address));
    if (b < 0) {
        printf("Confort: Problem occurred when binding a socket\n");
        exit(0);
    }

    /* Criar escuta do socket para aceitar conexões */
    l = listen(s, MAX_PENDING);
    if (l < 0) {
        printf("Confort: Problem accepting conections (listening)\n");
        exit(0);
    }

    /* Aguarda/aceita conexão */
    len = sizeof(client_sa);

    while(1) {
        newsoc = accept(s, (struct sockaddr *) &client_sa, &len);

        if(newsoc < 0){
            printf("Confort: Problem on creaing a new connection\n");
        }

        int pid = fork();
        /* pid = 0 => Processo pai
         * pid > 0 => Processo filho
         * pid < 0 => erro
         */
        if (pid < 0){
            printf("Confort: Failed to create a new fork\n");
            close(newsoc);
        } else if (pid > 0) {
            int i = getpeername(newsoc, (struct sockaddr *) &client_helper, &len);

            if (i < 0){
                printf("Confort: Failed to estabilsh connect\n");
            } else {
                printf("Confort: New client connected!\n");
                printf("Confort: Port: %d", ntohs(client_helper.sin_port));
                printf("\tFrom: %s\n", inet_ntoa(client_helper.sin_addr));

                if( recv(newsoc, (void*) buf, MAX_LINE, 0) ) {
                    printf("Confort: Message received\n");
                    printf("Confort: Port: %d", ntohs(client_helper.sin_port));
                    printf("Confort:   From: %s\n", inet_ntoa(client_helper.sin_addr));
                    printf("Confort: Message:\n %s\n", buf);
                }
                send(newsoc, (const void*) buf, strlen(buf) + 1, 0);
            }
        }
    }
    printf("Finishing Server\n");
    return 0;
}

#endif
