#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#include "provenance.h"

#define BUFSIZE 256

#define HELLO_WORLD "GET / HTTP/1.1\n\n"

int main(){
  int fd;
  int i;
  char buff[BUFSIZE];
  int sockfd, portno;
  struct sockaddr_in serveraddr;
  struct hostent *server;
  char *hostname;

  if(provenance_set_tracked(true)){
    printf("Failed Tracking, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
  }
  if(provenance_set_propagate(true)){
    printf("Failed propagate, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
  }

  fd = open("./LICENSE", O_RDONLY);

  for(i=0; i<5000; i++) {
      lseek(fd, 0, SEEK_SET);
      read(fd, &buff, BUFSIZE);
  }

  hostname = "www.google.com";
  portno = 80;

  /* socket: create the socket */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  /* gethostbyname: get the server's DNS entry */
  server = gethostbyname(hostname);

  /* build the server's Internet address */
  bzero((char *) &serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,
    (char *)&serveraddr.sin_addr.s_addr, server->h_length);
  serveraddr.sin_port = htons(portno);

  /* connect: create a connection with the server */
  if (connect(sockfd, (const struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
    printf("ERROR connecting\n");

  strncpy(buff, HELLO_WORLD, BUFSIZE);

  /* send the message to the server */
  write(sockfd, buff, strlen(buf));

  /* read the server's reply */
  bzero(buff, BUFSIZE);
  read(sockfd, buf, BUFSIZE);
  close(sockfd);

  for(i=0; i<5000; i++) {
      lseek(fd, 0, SEEK_SET);
      read(fd, &buff, BUFSIZE);
  }
  close(fd);
}
