/*
* CamFlow userspace IFC example
*
* Author: Thomas Pasquier <tfjmp2@cam.ac.uk>
*
* Copyright (C) 2016 University of Cambridge
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2, as
* published by the Free Software Foundation.
*
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/camflow.h>
#include <string.h>
#include <sys/wait.h>

#include "ifclib.h"

#define READ    0
#define WRITE   1

#define TEST_STR "Hello world!"

int main(void)
{
  int     fd[2], nbytes;
  pid_t   childpid;
  char    string[] = "Message one.";
  char    string2[] = "Another message.";
  char    readbuffer[80];
  struct ifc_context context;
  tag_t tag;
  int status;
  int i;

  tag = ifc_create_tag(&context);
  ifc_add_integrity(&context, tag);
  pipe(fd);

  if((childpid = fork()) == -1)
  {
    perror("fork");
    exit(1);
  }

  if(childpid == 0)
  {
    printf("Child:\n");
    ifc_get_context(&context);
    ifc_context_print(&context);
    close(fd[WRITE]);
    sleep(1);
    do{
      nbytes = read(fd[READ], readbuffer, 80);
      if(nbytes<=0){
        printf("Child failed reading %d\n", nbytes);
        if(nbytes==0)
          break;
      }else{
        printf("Received string(%d): %s\n", nbytes, readbuffer);
      }
      i++;
    }while(i<10);
  }
  else
  {
    printf("Parent:\n");
    ifc_get_context(&context);
    ifc_context_print(&context);
    close(fd[READ]);

    nbytes = write(fd[WRITE], string, (strlen(string)+1));
    if(nbytes<0){
      printf("Parent failed reading %d\n", nbytes);
    }else{
      printf("Wrote %d\n", nbytes);
    }

    ifc_remove_integrity(&context, tag);


    sleep(2);
    nbytes = write(fd[WRITE], string2, (strlen(string2)+1));
    if(nbytes <= 0){
      printf("Parent error (expected) %d\n", nbytes);
    }else{
      printf("Wrote %d\n", nbytes);
    }

    ifc_add_integrity(&context, tag);

    sleep(2);
    nbytes = write(fd[WRITE], string2, (strlen(string2)+1));
    if(nbytes <= 0){
      printf("Parent Error %d\n", nbytes);
    }else{
      printf("Wrote %d\n", nbytes);
    }
  }

  return 0;
}
