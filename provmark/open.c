#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  int fd;
  fd = open("./LICENSE", O_RDONLY);
}
