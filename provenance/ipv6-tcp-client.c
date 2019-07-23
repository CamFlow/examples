#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>

#include "provenance.h"


#define BUFSIZE 8192

#define HELLO_WORLD "IPv6 client message\n\n"

void error(char* msg) {
	perror(msg);
	exit(0);
}

int main(int argc, char **argv) {
	int sockfd, portno, n;
	struct sockaddr_in6 serveraddr;
	char buf[BUFSIZE];

	if (provenance_set_tracked(true)) {
		printf("Failed Tracking, error %d\n", errno);
		printf("%s\n\n", strerror(errno));
	}
	if (provenance_set_propagate(true)) {
		printf("Failed propagate, error %d\n", errno);
		printf("%s\n\n", strerror(errno));
	}

	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}
	portno = atoi(argv[1]);
	sockfd = socket(AF_INET6, SOCK_STREAM, 0);
	if (sockfd < 0) {
		error("ERROR opening socket");
	}

	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin6_family = AF_INET6;
	serveraddr.sin6_port = htons(portno);
	inet_pton(AF_INET6, "::1", &serveraddr.sin6_addr);

	if (connect(sockfd, (const struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
		error("ERROR connecting");

	strncpy(buf, HELLO_WORLD, BUFSIZE);

	n = write(sockfd, buf, strlen(buf));
	if (n < 0)
		error("ERROR writing to socket");

	bzero(buf, BUFSIZE);
	n = read(sockfd, buf, BUFSIZE);
	if (n < 0)
		error("ERROR reading from socket");

	close(sockfd);
	return 0;
}
