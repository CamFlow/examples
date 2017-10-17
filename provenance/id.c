#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provenance.h"

#define TARGET "/"
#define TARGET2 "/etc"

int main( void ){
  char buffer[256];
  provenance_file_id(TARGET, buffer, 256);
  printf("%s \t id is %s\n", TARGET, buffer);
  provenance_file_id(TARGET2, buffer, 256);
  printf("%s \t id is %s\n", TARGET2, buffer);
}
