#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
	int pid;
	char* pid_r;
	char input;
	FILE *fptr;

	printf("\n**Original file**\n\n");

	//Saving PID
	pid = getpid();
	fptr = fopen("my_pid.txt", "w");
	fprintf(fptr, "/proc/%d/exe", pid);
	fclose(fptr);

	fptr = fopen("my_pid.txt", "r");
	fscanf(fptr, "%s", pid_r);
	printf("the /proc/pid/exe path after reading is: %s\n", pid_r);
	

	//Termination
	printf("Enter \"e\" and then hit enter to terminate the program.\n");

	while(1){
		scanf("%c", &input);
		if(input == 'e'){
			break;
		}
	}
	return 0;
}