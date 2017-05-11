CC = gcc
CFLAGS = -g -Wall

all: client serever

run_client: client
	exec client localhost < echo Teste

run_server: server
	exec server

client: client.c
	$(CC) $(CFLAGS) client.c -o client

serever: server.c
	$(CC) $(CFLAGS) server.c -o server

clean: 
	rm -rf server client

