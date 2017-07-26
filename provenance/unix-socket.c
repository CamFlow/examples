/* A simple example to test UNIX socket */
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "provenancelib.h"

void error(char *msg)
{
    perror(msg);
    exit(1);
}

#define SOCK_PATH "/tmp/camflow_test.sock"
#define MESSAGE "This is a test"
#define MESSAGE2 "Second message"
#define MESSAGE3 "Server sent"

int main(int argc, char *argv[])
{
     pid_t childpid;
     struct sockaddr_un local, remote;
     int sk, sk2;
     int fd;
     int len;
     char buff[100];
     int done;
     int rc;

     if(provenance_set_tracked(true)){
       printf("Failed Tracking, error %d\n", errno);
       printf("%s\n\n",strerror(errno));
     }
     if(provenance_set_propagate(true)){
       printf("Failed propagate, error %d\n", errno);
       printf("%s\n\n",strerror(errno));
     }

     if((childpid = fork()) == -1)
     {
       perror("fork");
       exit(1);
     }

     if(childpid == 0){
       /* going to be the server */
       sk = socket(AF_UNIX, SOCK_STREAM, 0);
       if (sk < 0)
        error("Server failed creating.");
      local.sun_family = AF_UNIX;
      strcpy(local.sun_path, SOCK_PATH);
      unlink(local.sun_path);
      len = sizeof(local.sun_family)+strlen(local.sun_path);
      rc = bind(sk, (struct sockaddr*)&local, len);
      if(rc<0)
        error("Server failed binding.");
      rc = listen(sk, 5);
      if(rc<0)
        error("Server failed listening.");
      for(;;){
        len = sizeof(remote);
        sk2 = accept(sk, (struct sockaddr*)&remote, &len);
        if(sk2<0)
          error("Server failed accepting.");
        sleep(1);
        rc = recv(sk2, buff, 100, 0);
        if(rc <= 0)
          error("Server failed receiving.");
        rc = recv(sk2, buff, 100, 0);
        if(rc <= 0)
          error("Server failed receiving.");
        strcpy(buff, MESSAGE3);
        send(sk2, buff, 100, 0);
        close(sk2);
        break;
      }
     }else{
       sleep(1);
       /* going to be the client */
       sk = socket(AF_UNIX, SOCK_STREAM, 0);
       if (sk < 0)
        error("Client failed creating.");
      remote.sun_family = AF_UNIX;
      strcpy(remote.sun_path, SOCK_PATH);
      len = sizeof(remote.sun_family)+strlen(remote.sun_path);
      rc = connect(sk, (struct sockaddr*)&remote, len);
      if(rc<0)
        error("Client failed connecting.");
      strcpy(buff, MESSAGE);
      send(sk, buff, 100, 0);
      strcpy(buff, MESSAGE2);
      send(sk, buff, 100, 0);
      sleep(2);
      rc = recv(sk, buff, 100, 0);
      if(rc <= 0)
        error("Client failed receiving.");
     }
     close(sk);
     return 0;
}
