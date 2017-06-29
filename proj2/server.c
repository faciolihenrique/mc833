/* 2017
 * Projeto 2 - mc833 - Laboratório de Redes
 * server.c
 *
 * Henrique Noronha Facioli - 157986
 * Thiago Silva de Farias - 148077
 */

#include <sys/prctl.h>
#include <signal.h>
#include <time.h>

#include "main.h"
#include "server.h"
#include "colisions.h"

extern unsigned long int time_running;
extern pid_t pids[3];

////////////////////////////////////////////////////////////////////////////////

void create_router() {
    pid_t pid0 = fork();
    if (pid0 == 0) {
        prctl(PR_SET_PDEATHSIG, SIGKILL);
        create_entertainment_server();
    } else {
        pid_t pid1 = fork();
        if (pid1 == 0) {
            prctl(PR_SET_PDEATHSIG, SIGKILL);
            create_confort_server();
        } else {
            pid_t pid2 = fork();
            if (pid2 == 0) {
                prctl(PR_SET_PDEATHSIG, SIGKILL);
                create_security_server();
            } else {
                pids[0] = pid0;
                pids[1] = pid1;
                pids[2] = pid2;
                return;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
#ifdef SEC_TCP

int create_security_server() {
    AdjList* EnabledCars = calloc(1, sizeof(AdjList));
    struct sockaddr_in socket_address, client_sa;
    char* buf = calloc(PKG_ENT_SIZE, sizeof(char));
    int s, port, b, l, newsoc, speed;
    unsigned int len = sizeof(client_sa);;

    /* Define the port */
    port = SEC_PORT;
    printf("Starting TCP Security Server on %d\n", port);

    /* Get a new socket */
    s = socket(AF_INET, SOCK_STREAM, 0);
    if ( s < 0 ) {
        printf("Security: Problem occurred when creating a socket\n");
        exit(0);
    }

    /* Fill the socket_address */
    bzero((char *)&socket_address, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);
    socket_address.sin_addr.s_addr = INADDR_ANY;

    /* Binds the socket with the socket info */
    b = bind(s, (struct sockaddr *) &socket_address, sizeof(socket_address));
    if (b < 0) {
        printf("Security: Problem occurred when binding a socket\n");
        exit(0);
    }

    /* Starts listening */
    l = listen(s, MAX_PENDING);
    if (l < 0) {
        printf("Security: Problem accepting conections (listening)\n");
        exit(0);
    }

    newsoc = accept(s, (struct sockaddr *) &client_sa, &len);
    while(1){
        if(newsoc < 0){
            printf("Security: Problem on creaing a new connection\n");
        }
#ifndef NCURSES_SIMULATE
        if( recv(newsoc, (void*) buf, sizeof(SecPackageToServer), 0) ) {
            printf("Security: Message received");
            printf("\tFrom: %d\n", ((SecPackageToServer*) buf)->ID);
        }
#else
        recv(newsoc, (void*) buf, sizeof(SecPackageToServer), 0);
#endif

        /* Creates the package to send based on what it has returned */
        SecPackageToClient* rsp = calloc(1, sizeof(SecPackageToClient));
        rsp->ID = ((SecPackageToServer*) buf)->ID;
         /* Makes the analyses of the package received */
        rsp->ac = dealWithPackage(EnabledCars, (SecPackageToServer*) buf, &speed);
        rsp->car_speed = speed;
#ifdef DELAY
        struct timespec* ts = calloc(1, sizeof(struct timespec));
        ts->tv_sec = DELAY_SEC / 1000;
        ts->tv_nsec = (DELAY_SEC % 1000) * 1000000;
        nanosleep(ts, NULL);
        free(ts);
#endif

        send(newsoc, (const void*) rsp, sizeof(SecPackageToClient), 0);

        free(rsp);

        newsoc = accept(s, (struct sockaddr *) &client_sa, &len);
    }

    printf("Finishing Security Server\n");
    return 0;
}

#else

int create_security_server() {
    AdjList* EnabledCars = calloc(1, sizeof(AdjList));
    struct sockaddr_in so_server, client_sa;
    char buf[MAX_LINE];
    int len, s, port, b, cl_size, speed;

    port = SEC_PORT;
    printf("Starting UDP Security Server on %d\n", port);

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if ( s < 0 ) {
        printf("Security: Problem occurred when creating a socket\n");
        exit(0);
    }

    bzero((char *)&so_server, sizeof(so_server));
    so_server.sin_family = AF_INET;
    so_server.sin_port = htons(port);
    so_server.sin_addr.s_addr = INADDR_ANY;

    b = bind(s, (struct sockaddr *) &so_server, sizeof(so_server));
    if (b < 0) {
        printf("Security: Problem occurred when binding a socket\n");
        exit(0);
    }

	/* Aguarda/aceita conexão */
    cl_size = sizeof(client_sa);
    SecPackageToClient* rsp = calloc(1, sizeof(SecPackageToClient));
    while(1){
        len = 0;
        len = recvfrom(s, buf, sizeof(SecPackageToServer), 0, (struct sockaddr *) &client_sa, (socklen_t *)&cl_size);
        if (len < 0) {
            printf("Security: Problem occurred in recvfrom\n");
        } else if (len > 0) {
#ifndef NCURSES_SIMULATE
            printf("Security: Package received");
            printf("\tFrom: %d\n", ((SecPackageToServer*) buf)->ID);
#endif
            /* Creates the package to send based on what it has returned */
            rsp->ID = ((SecPackageToServer*) buf)->ID;
            rsp->ac = dealWithPackage(EnabledCars, (SecPackageToServer*) buf, &speed); /* Makes the analyses of the package received */
            rsp->car_speed = speed;
        }

#ifdef DELAY
        struct timespec* ts = calloc(1, sizeof(struct timespec));
        ts->tv_sec = DELAY_CON / 1000;
        ts->tv_nsec = (DELAY_CON % 1000) * 1000000;
        nanosleep(ts, NULL);
        free(ts);
#endif
        len = sendto(s, rsp, sizeof(SecPackageToClient), 0, (struct sockaddr *) &client_sa, cl_size);
        if (len < 0) {
            printf("Security: Problem occurred in sendto\n");
        }
    }
    printf("Finishing Security Server\n");

    return 0;
    exit(0);
}

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef ENT_TCP

int create_entertainment_server() {
    struct sockaddr_in socket_address, client_sa, client_helper;
    char buf[PKG_ENT_SIZE];
    unsigned int len;
    int s, port, b, l, newsoc;

    port = ENT_PORT;

    printf("Starting TCP Entertainment Server on %d\n", port);

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

        if (pid < 0){
            printf("Entertainment: Failed to create a new fork\n");
            close(newsoc);
        } else if (pid == 0) {
            prctl(PR_SET_PDEATHSIG, SIGKILL);
            int i = getpeername(newsoc, (struct sockaddr *) &client_helper, &len);

            if (i < 0){
                printf("Entertainment: Failed to estabilsh connect\n");
            } else {
#ifndef NCURSES_SIMULATE
                if( recv(newsoc, (void*) buf, sizeof(SecPackageToServer), 0) ) {
                    printf("Entertainment: Message received");
                    printf("\tFrom: %d\n", ((SecPackageToServer*) buf)->ID);
                }
#else
                recv(newsoc, (void*) buf, sizeof(SecPackageToServer), 0);
#endif

#ifdef DELAY
                struct timespec* ts = calloc(1, sizeof(struct timespec));
                ts->tv_sec = DELAY_ENT / 1000;
                ts->tv_nsec = (DELAY_ENT % 1000) * 1000000;
                nanosleep(ts, NULL);
                free(ts);
#endif

                char* pkg = calloc(PKG_ENT_SIZE, sizeof(char));
                strcpy(pkg, "ARE YOU NOT ENTERTAINED?\0");

                send(newsoc, (const void*) pkg, strlen(pkg)+1, 0);
                free(pkg);
            }
        }
    }
    printf("Finishing Entertainment Server\n");
    return 0;
}

#else

int create_entertainment_server() {
    struct sockaddr_in so_server, client_sa;
    char* buf = calloc(PKG_ENT_SIZE, sizeof(char));
    int s, port, b, len, cl_size;

    port = ENT_PORT;
    printf("Starting UDP Entertainment Server on %d\n", port);

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if ( s < 0 ) {
        printf("Entertainment: Problem occurred when creating a socket\n");
        exit(0);
    }

    /* Criação da estrutura de dados de endereço */
    bzero((char *)&so_server, sizeof(so_server));
    so_server.sin_family = AF_INET;
    so_server.sin_port = htons(port);
    so_server.sin_addr.s_addr = INADDR_ANY;

    /* Associar socket ao descritor */
    b = bind(s, (struct sockaddr *) &so_server, sizeof(so_server));
    if (b < 0) {
        printf("Entertainment: Problem occurred when binding a socket\n");
        exit(0);
    }

    /* Aguarda/aceita conexão */
    cl_size = sizeof(client_sa);
    while(1){
        len = 0;
        len = recvfrom(s, buf, PKG_ENT_SIZE, 0, (struct sockaddr *) &client_sa, (socklen_t *)&cl_size);
        if (len < 0) {
            printf("Entertainment: Problem occurred in recvfrom\n");
        }

        char* pkg = calloc(PKG_ENT_SIZE, sizeof(char));
        strcpy(pkg, "ARE YOU NOT ENTERTAINED?\0");

#ifdef DELAY
        struct timespec* ts = calloc(1, sizeof(struct timespec));
        ts->tv_sec = DELAY_ENT / 1000;
        ts->tv_nsec = (DELAY_ENT % 1000) * 1000000;
        nanosleep(ts, NULL);
        free(ts);
#endif
        len = sendto(s, pkg, PKG_ENT_SIZE, 0, (struct sockaddr *) &client_sa, cl_size);
        if (len < 0) {
            printf("Entertainment: Problem occurred in sendto\n");
        }
    }
    printf("Finishing Entertainment Server\n");

    return 0;
    exit(0);
}

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef CON_TCP
int create_confort_server() {

    struct sockaddr_in socket_address, client_sa, client_helper;
    char buf[PKG_CON_SIZE];
    unsigned int len;
    int s, port, b, l, newsoc;

    port = CON_PORT;
    printf("Starting TCP Confort Server on %d\n", port);

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

        if (pid < 0){
            printf("Confort: Failed to create a new fork\n");
            close(newsoc);
        } else if (pid == 0) {
            prctl(PR_SET_PDEATHSIG, SIGKILL);
            int i = getpeername(newsoc, (struct sockaddr *) &client_helper, &len);

            if (i < 0){
                printf("Confort: Failed to estabilsh connect\n");
            } else {
#ifndef NCURSES_SIMULATE
                if( recv(newsoc, (void*) buf, sizeof(SecPackageToServer), 0) ) {
                    printf("Confort: Message received");
                    printf("\tFrom: %d\n", ((SecPackageToServer*) buf)->ID);
                }
#else
                recv(newsoc, (void*) buf, sizeof(SecPackageToServer), 0);
#endif

                char* pkg = calloc(PKG_CON_SIZE, sizeof(char));
                strcpy(pkg, "I WILL LOOK FOR YOU, I WILL FIND YOU AND I WILL... COMFORT YOU.\0");

#ifdef DELAY
                struct timespec* ts = calloc(1, sizeof(struct timespec));
                ts->tv_sec = DELAY_CON / 1000;
                ts->tv_nsec = (DELAY_CON % 1000) * 1000000;
                nanosleep(ts, NULL);
                free(ts);
#endif

                send(newsoc, (const void*) pkg, strlen(pkg)+1, 0);
                free(pkg);
            }
        }
    }
    printf("Finishing Confort Server\n");
    return 0;
}

#else

int create_confort_server() {
    struct sockaddr_in so_server, client_sa;
    char* buf = calloc(PKG_CON_SIZE, sizeof(char));
    int s, port, b, len, cl_size;

    port = CON_PORT;
    printf("Starting UDP Confort Server on %d\n", port);

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if ( s < 0 ) {
        printf("Confort: Problem occurred when creating a socket\n");
        exit(0);
    }

    /* Criação da estrutura de dados de endereço */
    bzero((char *)&so_server, sizeof(so_server));
    so_server.sin_family = AF_INET;
    so_server.sin_port = htons(port);
    so_server.sin_addr.s_addr = INADDR_ANY;

    /* Associar socket ao descritor */
    b = bind(s, (struct sockaddr *) &so_server, sizeof(so_server));
    if (b < 0) {
        printf("Confort: Problem occurred when binding a socket\n");
        exit(0);
    }

    /* Aguarda/aceita conexão */
    cl_size = sizeof(client_sa);
    while(1){
        len = 0;
        len = recvfrom(s, buf, PKG_CON_SIZE, 0, (struct sockaddr *) &client_sa, (socklen_t *)&cl_size);
        if (len < 0) {
            printf("Confort: Problem occurred in recvfrom\n");
        }

        char* pkg = calloc(PKG_CON_SIZE, sizeof(char));
        strcpy(pkg, "I WILL LOOK FOR YOU, I WILL FIND YOU AND I WILL... COMFORT YOU.\0");

#ifdef DELAY
        struct timespec* ts = calloc(1, sizeof(struct timespec));
        ts->tv_sec = DELAY_CON / 1000;
        ts->tv_nsec = (DELAY_CON % 1000) * 1000000;
        nanosleep(ts, NULL);
        free(ts);
#endif

        len = sendto(s, pkg, PKG_CON_SIZE, 0, (struct sockaddr *) &client_sa, cl_size);
        if (len < 0) {
            printf("Confort: Problem occurred in sendto\n");
        }
    }
    printf("Finishing Confort Server\n");

    return 0;
    exit(0);
}

#endif
