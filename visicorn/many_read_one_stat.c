#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "provenance.h"

int main(){
  int fd;
  int i;
  char buff[256];
  struct stat s;

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
      read(fd, &buff, 256);
  }

  for (i=0; i<10; i++) {
      stat(fd, &s);

  for(i=0; i<5000; i++) {
      lseek(fd, 0, SEEK_SET);
      read(fd, &buff, 256);
  }
  close(fd);
}
