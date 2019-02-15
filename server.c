#include "server.h"
#define BASE_USERS 3

struct server_state *init_server();
void main_loop(struct server_state *state);

int online_users = 0;

int main()
{
	struct server_state *state = init_server();
	state->user = malloc (sizeof(struct user) * BASE_USERS);

	main_loop(state);
	return 0;
}

void main_loop(struct server_state *state)
{
	int user_socket = 0;
	int addrlen = sizeof(state->address);
	while (1) {
		if((state->user[online_users].user_socket = accept(state->server_socket, (struct sockaddr *)&state->address, (socklen_t *)&addrlen)) < 0) {
			printf ("Unable to accept connection.\n");
			exit(EXIT_FAILURE);
		}

		create_user_thread(state, user_socket);
	}
}

struct server_state *init_server()
{
	struct server_state state;

	if ((socket = create_socket()))
		setup_socket(&state);
	else {
		printf("Unable to setup socket.\n");
		exit(EXIT_FAILURE);
	}

	return socket;
}

int create_socket()
{
	int new_socket = socket(AF_INET, SOCK_STREAM, 0);

	return (new_socket > 0) ? new_socket : 0;
}

void setup_socket(int *state)
{
	state->address.sin_family = AF_INET;
	state->address.sin_port = htons (8080);
	state->address.sin_addr.s_addr = INADDR_ANY;

	if((setsockopt(state->socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 0, 0)) {
		printf("Unable to set socket options.\n");
		exit(EXIT_FAILURE);
	}

	if ((bind(state->socket, (struct sockaddr *)&state->address, sizeof(state->address)) < 0) {
		printf ("Unable to bind socket.\n");
		exit(EXIT_FAILURE);
	}

	if ((listen(state->socket, 5)) < 0) {
		printf("Listen error.\n");
		exit(EXIT_FAILURE);
	}
}
