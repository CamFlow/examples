#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "provenance.h"

int main(int argc, char *argv[]){
	char *path;
	int result;
	int fd;
	char buffer[1];

	if(provenance_set_tracked(true)){
    printf("Failed Tracking, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
  }

	buffer[0] = 'X';

	path = "/tmp/testfile";

	fd = open(path, O_CREAT|O_WRONLY, 0666);
	if(fd < 0){
		perror("Failed to open file!");
		return -1;
	}

	result = write(fd, (void *)(&buffer[0]), 1);
	if(result < 0){
		perror("Failed to write file!");
	}else{
		fsync(fd);
	}

	close(fd);

	return 0;
}
