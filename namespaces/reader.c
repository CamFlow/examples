#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "provenance.h"

int main(int argc, char *argv[]){
	char *path;
	int result;
	int fd;
	char *buffer;
	int unshareResult;

	if(provenance_set_tracked(true)){
    printf("Failed Tracking, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
  }

  buffer = (char *)malloc(sizeof(char) * 1);

	unshareResult = unshare(CLONE_NEWIPC);
	if(unshareResult < 0){
		perror("Failed to unshare IPC!");
		return -1;
	}

	path = "/tmp/testfile";

	fd = open(path, O_RDONLY);
	if(fd < 0){
		perror("Failed to open file!");
		return -1;
	}

	result = read(fd, (void *)(buffer), 1);
	if(result < 0)
		perror("Failed to read file!");

	close(fd);

	unlink(path);

	return 0;
}
