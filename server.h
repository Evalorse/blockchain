#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

struct user
{
	int id, socket;
}

struct server_state
{
	int server_socket;
	int online_users;

	struct user *user;
	struct sockaddr_in address;
};

struct server_state *init_server();
void main_loop(struct server_state *state);
