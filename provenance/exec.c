#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provenancelib.h"

#define PROGRAM "./provenance/pipe.o"

int main( void ){
  char *envp[] = { "aa", "bb", NULL };
  char *argv[] = {PROGRAM , "test", "test", NULL};

  if(provenance_set_tracked(true)){
    printf("Failed Tracking, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
  }
  if(provenance_set_propagate(true)){
    printf("Failed propagate, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
  }
  execve(PROGRAM, argv, envp);
}
