#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#define LISTEN_PORT 12345
#define MAX_PENDING 5
#define MAX_LINE 256

int main()
{
	struct sockaddr_in socket_address;
    char buf[MAX_LINE];
    unsigned int len;
    int s, new_s;

    /* criação da estrutura de dados de endereço */
    bzero((char *)&socket_address, sizeof(socket_address));
	(...)
	/* criação de socket passivo */
	(...)
	/* Associar socket ao descritor */
	(...)
	/* Criar escuta do socket para aceitar conexões */
	(...)
        /* aguardar/aceita conexão, receber e imprimir texto na tela, enviar eco */
	(...)
}


