#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#define LISTEN_PORT 12345
#define MAX_PENDING 5
#define MAX_LINE 256

//sin_addr-s_addrhtonl(INADDR_ANY)

int main() {
	struct sockaddr_in socket_address;
    char buf[MAX_LINE];
    unsigned int len;
    int s, new_s;
    
    /* Checking arguments */
    if (argc < 2){
        printf("Missing Host Address");
        return -1;
    } else if (argc < 3){
        port = SERVER_PORT;
    } else {
        port = atoi(argv[2]);
    }
    
    /* criação da estrutura de dados de endereço */
    bzero((char *)&socket_address, sizeof(socket_address));
	/* criação de socket passivo */
	/* Associar socket ao descritor */
    /* Criar escuta do socket para aceitar conexões */
	/* aguardar/aceita conexão, receber e imprimir texto na tela, enviar eco */
}


