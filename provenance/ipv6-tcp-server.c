#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provenance.h"

void error(char *msg) {
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]) {
	int sockfd, newsockfd, portno, clilen, i=0;
	char buffer[8192];
	struct sockaddr_in6 serv_addr, cli_addr;
	int n;

	if (provenance_set_tracked(true)) {
		printf("Failed Tracking, error %d\n", errno);
		printf("%d\n\n", strerror(errno));
	}
	if (provenance_set_propagate(true)) {
		printf("Failed propagate, error%d\n", errno);
		printf("%s\n\n", strerror(errno));
	}

	if (argc < 2) {
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET6, SOCK_STREAM, 0);
	if (sockfd < 0) {
		error("ERROR opening socket");
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin6_family = AF_INET6;
	serv_addr.sin6_addr = in6addr_any;
	serv_addr.sin6_port = htons(portno);

	printf("Binding...\n");
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");
	printf("Listening...\n");
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	do {
		printf("\n\n___________________\n");
		printf("Request #%d\n", i++);
		printf("Accepting...\n");
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0) {
			error("ERROR on accept");
		}
		bzero(buffer, 8192);

		printf("Reading...\n");
		n = read(newsockfd, buffer, 8191);
		if (n < 0) error("ERROR reading from socket");
		printf("Here is the message: %s\n", buffer);

		printf("Writing...\n");
		n = write(newsockfd, "I got your message", 18);
		if (n < 0) error("ERROR writing to socket");

		printf("Closing...\n");
		close(newsockfd);
	} while(1);
	close(sockfd);
	return 0;
}
