#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provenance.h"

int main( void ){
  int fd[2];
  pid_t   childpid;
  char readbuffer[80];
  int i;

  if(provenance_set_tracked(true)){
    printf("Failed Tracking, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
  }
  if(provenance_set_propagate(true)){
    printf("Failed propagate, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
  }
  pipe(fd);
  if((childpid = fork()) == -1)
  {
          perror("fork");
          exit(1);
  }

  if(childpid == 0)
  {
          close(fd[0]);

          for (i=0; i<50; i++)
            write(fd[1], "test", 4);
          exit(0);
  }
  else
  {
          /* Parent process closes up output side of pipe */
          close(fd[1]);
          sleep(1);
          for (i=0; i<50; i++)
            read(fd[0], readbuffer, sizeof(readbuffer));
  }
  return 0;
}
