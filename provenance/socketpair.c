#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provenance.h"

#define CHILD 0
#define PARENT 1

int main( void ){
  int fd[2];
  pid_t pid;
  char buffer[256];
  char message[] = "hello world!";

  if(provenance_set_tracked(true)){
    printf("Failed Tracking, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
  }
  if(provenance_set_propagate(true)){
    printf("Failed propagate, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
  }
  socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);

  pid = fork();

  if (pid == 0) {
    close(fd[PARENT]);
    write(fd[CHILD], message, sizeof(message));
  } else {
    close(fd[CHILD]);
    read(fd[PARENT], buffer, 256);
    printf("%s\n", buffer);
  }
  exit(0);
}
