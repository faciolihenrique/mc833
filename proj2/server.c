/* 2017
 * Projeto 2 - mc833 - Laboratório de Redes
 * server.c
 *
 * Henrique Noronha Facioli - 157986
 * Thiago Silva de Farias - 148077
 */

#include "main.h"
#include "server.h"

void create_router() {
    if(fork()){
        if(fork()){
            create_security_server();
        } else {
            if (fork()) {
                create_entertainment_server();
            } else {
                if (fork()) {
                    create_confort_server();
                } else {
                    while(1);
                }
            }
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
    struct sockaddr_in socket_address, client_helper;
    char buf[MAX_LINE];
    unsigned int len;
    int s, port, b, l, newsoc, maxfd, sockfd, cliente_num, nready, i, clientes[N_CONNECTIONS];
    fd_set todos_fds, novo_set;

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
        printf("Problem occurred when creating security socket\n");
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
        printf("Problem occurred when binding a security socket\n");
        return -3;
    }

    /* Criar escuta do socket para aceitar conexões */
    l = listen(s, MAX_PENDING);
    if (l < 0) {
        printf("Problem accepting security conections (listening)\n");
        return -3;
    }

    /* Inicializa os clientes */
    maxfd = s;
    cliente_num = -1;
    for (i = 0; i < N_CONNECTIONS; i++)
        clientes[i] = -1;

    FD_ZERO(&todos_fds);
    FD_SET(s, &todos_fds);

    while(1){
        novo_set = todos_fds;
        nready = select(maxfd+1, &novo_set, NULL, NULL, NULL);
        if(nready < 0) {
            printf("Failed to use select on security\n");
            return -4;
        }

        /* Se algo acontecer no socket s - é uma conexão nova */
        if(FD_ISSET(s, &novo_set)) {
            len = sizeof(socket_address);

            /* Cria um novo socket de entrada */
            newsoc = accept(s, (struct sockaddr *)&socket_address, &len);
            /* Problema na conexao */
            if(newsoc < 0) {
                printf("Problem on creating a new security connection\n");
                return -5;
            }

            /* Imprime informações desse novo socket */
            int t = getpeername(newsoc, (struct sockaddr *) &client_helper, &len);
            if (t < 0){
                printf("Failed to estabilsh security connect\n");
            } else {
                printf("New security client connected!\n");
                printf("Port: %d", ntohs(client_helper.sin_port));
                printf("\tFrom: %s\n", inet_ntoa(client_helper.sin_addr));
            }


            /* Adiciona o novo socket no vetor de clientes */
            for (i = 0; i < N_CONNECTIONS; i++) {
                if (clientes[i] < 0) {
                    clientes[i] = newsoc;
                    break;
                }
            }
            if (i == N_CONNECTIONS) {
                printf("Maximum number of clients already established\n");
                    return -6;
            }

            FD_SET(newsoc, &todos_fds);		// Adiciona novo descritor ao conjunto
            if (newsoc > maxfd)
                maxfd = newsoc;			    // para o select
            if (i > cliente_num)
                cliente_num = i;	       	// Indice máximo no vetor clientes[]
            if (--nready <= 0)
                continue;		         	// Não existem mais descritores para serem lidos
        }

        /* Verifica se há novas entradas nos sockets dos clientes */
        for (i = 0; i <= cliente_num; i++) {
            sockfd = clientes[i];
            /* Se for >= 0 então existe um sockfd */
            if (sockfd >= 0) {

                len = sizeof(client_helper);
                getpeername(sockfd, (struct sockaddr *) &client_helper, &len);

                /* Se há modificação no socket - então ou recebeu mensagem ou
                 * teve alguma desconexão
                 */
                if (FD_ISSET(sockfd, &novo_set)) {
                    if ( recv(sockfd, (void*) buf, MAX_LINE, 0) ) {
                        printf("Message received\n");
                        printf("Port: %d", ntohs(client_helper.sin_port));
                        printf("  From: %s\n", inet_ntoa(client_helper.sin_addr));
                        printf("Message:\n %s\n", buf);

                        /* Envia resposta */
                        send(sockfd, (const void*) buf, strlen(buf) + 1, 0);
                    } else {
                        printf("Disconected %s on Port %d \n" ,
                                inet_ntoa(client_helper.sin_addr) ,
                                ntohs(client_helper.sin_port)
                                );
                        close(sockfd);
                        FD_CLR(sockfd, &todos_fds);
                        clientes[i] = -1;
                    }
                    if (--nready <= 0)
                        break;  // Não existem mais descritores para serem lidos
                }
            }
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

int create_entertainment_server() {
    struct sockaddr_in socket_address, client_helper;
    char buf[MAX_LINE];
    unsigned int len;
    int s, port, b, l, newsoc, maxfd, sockfd, cliente_num, nready, i, clientes[N_CONNECTIONS];
    fd_set todos_fds, novo_set;

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
        printf("Problem occurred when creating entertainment socket\n");
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
        printf("Problem occurred when binding a entertainment socket\n");
        return -3;
    }

    /* Criar escuta do socket para aceitar conexões */
    l = listen(s, MAX_PENDING);
    if (l < 0) {
        printf("Problem accepting entertainment conections (listening)\n");
        return -3;
    }

    /* Inicializa os clientes */
    maxfd = s;
    cliente_num = -1;
    for (i = 0; i < N_CONNECTIONS; i++)
        clientes[i] = -1;

    FD_ZERO(&todos_fds);
    FD_SET(s, &todos_fds);

    while(1){
        novo_set = todos_fds;
        nready = select(maxfd+1, &novo_set, NULL, NULL, NULL);
        if(nready < 0) {
            printf("Failed to use select on entertainment\n");
            return -4;
        }

        /* Se algo acontecer no socket s - é uma conexão nova */
        if(FD_ISSET(s, &novo_set)) {
            len = sizeof(socket_address);

            /* Cria um novo socket de entrada */
            newsoc = accept(s, (struct sockaddr *)&socket_address, &len);
            /* Problema na conexao */
            if(newsoc < 0) {
                printf("Problem on creating a new entertainment connection\n");
                return -5;
            }

            /* Imprime informações desse novo socket */
            int t = getpeername(newsoc, (struct sockaddr *) &client_helper, &len);
            if (t < 0){
                printf("Failed to estabilsh entertainment connect\n");
            } else {
                printf("New entertainment client connected!\n");
                printf("Port: %d", ntohs(client_helper.sin_port));
                printf("\tFrom: %s\n", inet_ntoa(client_helper.sin_addr));
            }


            /* Adiciona o novo socket no vetor de clientes */
            for (i = 0; i < N_CONNECTIONS; i++) {
                if (clientes[i] < 0) {
                    clientes[i] = newsoc;
                    break;
                }
            }
            if (i == N_CONNECTIONS) {
                printf("Maximum number of clients already established\n");
                    return -6;
            }

            FD_SET(newsoc, &todos_fds);		// Adiciona novo descritor ao conjunto
            if (newsoc > maxfd)
                maxfd = newsoc;			    // para o select
            if (i > cliente_num)
                cliente_num = i;	       	// Indice máximo no vetor clientes[]
            if (--nready <= 0)
                continue;		         	// Não existem mais descritores para serem lidos
        }

        /* Verifica se há novas entradas nos sockets dos clientes */
        for (i = 0; i <= cliente_num; i++) {
            sockfd = clientes[i];
            /* Se for >= 0 então existe um sockfd */
            if (sockfd >= 0) {

                len = sizeof(client_helper);
                getpeername(sockfd, (struct sockaddr *) &client_helper, &len);

                /* Se há modificação no socket - então ou recebeu mensagem ou
                 * teve alguma desconexão
                 */
                if (FD_ISSET(sockfd, &novo_set)) {
                    if ( recv(sockfd, (void*) buf, MAX_LINE, 0) ) {
                        printf("Message received\n");
                        printf("Port: %d", ntohs(client_helper.sin_port));
                        printf("  From: %s\n", inet_ntoa(client_helper.sin_addr));
                        printf("Message:\n %s\n", buf);

                        /* Envia resposta */
                        send(sockfd, (const void*) buf, strlen(buf) + 1, 0);
                    } else {
                        printf("Disconected %s on Port %d \n" ,
                                inet_ntoa(client_helper.sin_addr) ,
                                ntohs(client_helper.sin_port)
                                );
                        close(sockfd);
                        FD_CLR(sockfd, &todos_fds);
                        clientes[i] = -1;
                    }
                    if (--nready <= 0)
                        break;				// Não existem mais descritores para serem lidos
                }
            }
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

int create_confort_server() {
    struct sockaddr_in socket_address, client_helper;
    char buf[MAX_LINE];
    unsigned int len;
    int s, port, b, l, newsoc, maxfd, sockfd, cliente_num, nready, i, clientes[N_CONNECTIONS];
    fd_set todos_fds, novo_set;

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
        printf("Problem occurred when creating confort socket\n");
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
        printf("Problem occurred when binding a confort socket\n");
        return -3;
    }

    /* Criar escuta do socket para aceitar conexões */
    l = listen(s, MAX_PENDING);
    if (l < 0) {
        printf("Problem accepting confort conections (listening)\n");
        return -3;
    }

    /* Inicializa os clientes */
    maxfd = s;
    cliente_num = -1;
    for (i = 0; i < N_CONNECTIONS; i++)
        clientes[i] = -1;

    FD_ZERO(&todos_fds);
    FD_SET(s, &todos_fds);

    while(1){
        novo_set = todos_fds;
        nready = select(maxfd+1, &novo_set, NULL, NULL, NULL);
        if(nready < 0) {
            printf("Failed to use select on confort\n");
            return -4;
        }

        /* Se algo acontecer no socket s - é uma conexão nova */
        if(FD_ISSET(s, &novo_set)) {
            len = sizeof(socket_address);

            /* Cria um novo socket de entrada */
            newsoc = accept(s, (struct sockaddr *)&socket_address, &len);
            /* Problema na conexao */
            if(newsoc < 0) {
                printf("Problem on creating a new confort connection\n");
                return -5;
            }

            /* Imprime informações desse novo socket */
            int t = getpeername(newsoc, (struct sockaddr *) &client_helper, &len);
            if (t < 0){
                printf("Failed to estabilsh confort connect\n");
            } else {
                printf("New confort client connected!\n");
                printf("Port: %d", ntohs(client_helper.sin_port));
                printf("\tFrom: %s\n", inet_ntoa(client_helper.sin_addr));
            }


            /* Adiciona o novo socket no vetor de clientes */
            for (i = 0; i < N_CONNECTIONS; i++) {
                if (clientes[i] < 0) {
                    clientes[i] = newsoc;
                    break;
                }
            }
            if (i == N_CONNECTIONS) {
                printf("Maximum number of clients already established\n");
                    return -6;
            }

            FD_SET(newsoc, &todos_fds);		// Adiciona novo descritor ao conjunto
            if (newsoc > maxfd)
                maxfd = newsoc;			    // para o select
            if (i > cliente_num)
                cliente_num = i;	       	// Indice máximo no vetor clientes[]
            if (--nready <= 0)
                continue;		         	// Não existem mais descritores para serem lidos
        }

        /* Verifica se há novas entradas nos sockets dos clientes */
        for (i = 0; i <= cliente_num; i++) {
            sockfd = clientes[i];
            /* Se for >= 0 então existe um sockfd */
            if (sockfd >= 0) {

                len = sizeof(client_helper);
                getpeername(sockfd, (struct sockaddr *) &client_helper, &len);

                /* Se há modificação no socket - então ou recebeu mensagem ou
                 * teve alguma desconexão
                 */
                if (FD_ISSET(sockfd, &novo_set)) {
                    if ( recv(sockfd, (void*) buf, MAX_LINE, 0) ) {
                        printf("Message received\n");
                        printf("Port: %d", ntohs(client_helper.sin_port));
                        printf("  From: %s\n", inet_ntoa(client_helper.sin_addr));
                        printf("Message:\n %s\n", buf);

                        /* Envia resposta */
                        send(sockfd, (const void*) buf, strlen(buf) + 1, 0);
                    } else {
                        printf("Disconected %s on Port %d \n" ,
                                inet_ntoa(client_helper.sin_addr) ,
                                ntohs(client_helper.sin_port)
                                );
                        close(sockfd);
                        FD_CLR(sockfd, &todos_fds);
                        clientes[i] = -1;
                    }
                    if (--nready <= 0)
                        break;	// Não existem mais descritores para serem lidos
                }
            }
        }
    }
    return 0;
}

#endif
