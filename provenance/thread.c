#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "provenance.h"

void *print_message_function( void *ptr );

int main()
{
     pthread_t thread1, thread2;
     char *message1 = "Thread 1";
     char *message2 = "Thread 2";
     int  iret1, iret2;

     if(provenance_set_tracked(true)){
       printf("Failed Tracking, error %d\n", errno);
       printf("%s\n\n",strerror(errno));
     }
     if(provenance_set_propagate(true)){
       printf("Failed propagate, error %d\n", errno);
       printf("%s\n\n",strerror(errno));
     }
    /* Create independent threads each of which will execute function */
     iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);
     iret2 = pthread_create( &thread2, NULL, print_message_function, (void*) message2);
     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL);
     exit(0);
}

void *print_message_function( void *ptr )
{
     char *message;
     message = (char *) ptr;
     char file_name[100];
     int cc = snprintf(file_name,100,"/tmp/output_threadid_%lu",syscall(SYS_gettid));
     file_name[cc] = '\0';
     FILE *fp;
     fp = fopen(file_name,"w");
     fputs(message, fp);
     fclose(fp);
}
