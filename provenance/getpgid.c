#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provenance.h"

int main(int argc, char **argv){
  int pid;
  int gr;
  if (argc < 2) {
    printf("You need to pass a pid");
    return -1;
  }
  if(provenance_set_tracked(true)){
    printf("Failed Tracking, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
  }
  if(provenance_set_propagate(true)){
    printf("Failed propagate, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
  }
  pid = atoi(argv[1]);
  gr = getpgid(pid);
}
