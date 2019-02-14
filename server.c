#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "server.h"

struct server_state *init_server();

int main()
{
	struct server_state *state = init_server();
	return 0;
}

struct server_state *init_server()
{
	int socket;
	
	if ((socket = create_socket())) {
		setup_socket(&socket);
	}
	
	return socket;
}

int create_socket()
{
	int new_socket = socket(AF_INET, SOCK_STREAM, 0);
	return (new_socket > 0) ? new_socket : 0;
}

void setup_socket(int *socket)
{
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons (8080);
	address.sin_addr.s_addr = INADDR_ANY;
	
	if((setsockopt(*socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 0, 0)) {
		printf("Unable to set socket options.\n");
		exit(EXIT_FAILURE);
	}
	
	if ((bind(*socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
		printf ("Unable to bind socket.\n");
		exit(EXIT_FAILURE);
	}
	
	if ((listen(*socket, 5)) < 0) {
		printf("Listen error.\n");
		exit(EXIT_FAILURE);
	}
}
