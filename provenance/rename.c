#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provenance.h"

int main( void ){
  if(provenance_set_propagate(true)){
    printf("Failed propagate, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
  }
  rename("./provenance/input.txt", "./provenance/rename_input.txt");
  provenance_propagate_file("./provenance/rename_input.txt", false);
  if(provenance_set_propagate(false )){
    printf("Failed propagate, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
  }
  return 0;
}
