CC = gcc
CFLAGS = -g -Wall

all: client serever

run_client: client
	exec client localhost < echo Teste

run_server: server
	exec server

client: client.c
	$(CC) $(CFLAGS) client.c -o client.out

serever: server.c
	$(CC) $(CFLAGS) server.c -o server.out

clean:
	rm -rf server.out client.out
