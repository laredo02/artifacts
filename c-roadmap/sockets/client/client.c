
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNUM 9090
#define MAXLEN 512

int main (int argc, const char **argv) {

	char buffer[MAXLEN+1];

	int socket_fd;
	struct sockaddr_in server, client;

	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("ERROR: couldn't create socket");
		exit(1);
	}

	memset(&server, 0, sizeof(server));

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(PORTNUM);

	int connected = connect(socket_fd, (struct sockaddr *)&server, sizeof(struct sockaddr_in));
	if (connected != 0) {
		perror("ERROR");
		exit(1);
	}

	ssize_t len;
	if ((len = recv(socket_fd, buffer, MAXLEN, 0)) == -1) {
		perror("ERROR");
		exit(1);
	}

	buffer[len] = '\n';
	printf("%s\n", buffer);

	close(socket_fd);
	return 0;
}

