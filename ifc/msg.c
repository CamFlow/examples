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
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#include "ifclib.h"

#define READ    0
#define WRITE   1

#define TEST_STR "Hello world!"

#define MSGTYPE 1

struct msgmsg {
  long      mtype;    /* message type */
  char mtext[64]; /* message text of length MSGSZ */
};

#define MSGSZ (sizeof(struct msgmsg) - sizeof(long))

int main(void)
{
  struct ifc_context context;
  tag_t tag;
  pid_t   childpid;
  key_t key;
  int msqid;
  struct msgmsg msg;

  srand(time(NULL));
  key =rand();

  tag = ifc_create_tag(&context);
  ifc_add_integrity(&context, tag);

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
    key = ftok("/tmp", key);
    printf("key: %u\n");
    if((msqid = msgget(key, (IPC_CREAT | 0666)))==-1){
      perror("error msgget");
      exit(1);
    }
    if (msgrcv(msqid, &msg, MSGSZ, MSGTYPE, 0) == -1)
      perror("msgop: msgrcv failed");
    printf("Read: %s\n", msg.mtext);

    if (msgrcv(msqid, &msg, MSGSZ, MSGTYPE, 0) == -1)
      perror("msgop: msgrcv failed");
    printf("Read: %s\n", msg.mtext);
  }
  else
  {
    printf("Parent:\n");
    ifc_get_context(&context);
    ifc_context_print(&context);
    key = ftok("/tmp", key);
    printf("key: %u\n");
    if((msqid = msgget(key, (IPC_CREAT | 0666)))==-1){
      perror("error msgget");
      exit(1);
    }
    sprintf(msg.mtext, "Sending message #%u", 1);
    msg.mtype = MSGTYPE;
    if (msgsnd(msqid, &msg, MSGSZ, 0) == -1)
      perror("msgop: msgsnd failed");

    ifc_remove_integrity(&context, tag);

    /* this message will never reach destination */
    sprintf(msg.mtext, "Sending message #%u", 2);
    msg.mtype = MSGTYPE;
    if (msgsnd(msqid, &msg, MSGSZ, 0) == -1)
      perror("msgop: msgsnd failed");

    ifc_add_integrity(&context, tag);

    /* this one will */
    sprintf(msg.mtext, "Sending message #%u", 3);
    msg.mtype = MSGTYPE;
    if (msgsnd(msqid, &msg, MSGSZ, 0) == -1)
      perror("msgop: msgsnd failed");
  }

  return 0;
}
