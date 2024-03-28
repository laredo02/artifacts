
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORTNUM 9090

int main (int argc, const char **argv) {

	struct sockaddr_in server;

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(PORTNUM);

	int socket_fd;
	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("ERROR:");
		exit(1);
	}

	if (bind(socket_fd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) {
		perror("ERROR:");
		exit(1);
	}
	if (listen(socket_fd, 1) == -1) {
		perror("ERROR");
		exit(1);
	}

	struct sockaddr_in client;
	int socksize;
	int socket_connection = accept(socket_fd, (struct sockaddr *)&client, &socksize);

	while (socket_connection) {
		printf("%s: ", inet_ntoa(client.sin_addr));
		char *msg = "HolaMundo\nHolaMundo\n";
		send(socket_connection, "HolaMundo", strlen(msg),0);
		socket_connection = accept(socket_fd, (struct sockaddr *)&client, &socksize);
	}

	close(socket_fd);
	return 0;
}

