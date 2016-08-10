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
#include <sys/socket.h>
#include <linux/netlink.h>
#include <string.h>

#include "ifclib.h"
#define TEST_MSG "this is a test message!"
#define TEST_MSG2 "a second one."
#define TEST_MSG3 "and the last and third one."

#define FILE_PATH "/tmp/bridge-example.log"

struct logger_msg{
  struct ifc_bridge_msg ifc_info;
  char data[1024];
};

int main(void){
  struct sockaddr_nl dest_addr;
  struct nlmsghdr *nlh = NULL;
  struct iovec iov;
  struct msghdr msg;
  struct logger_msg lmsg;
  int fd = ifc_create_bridge_socket();
  pid_t pid = getpid(), rpid;
  char message[1024];
  struct ifc_context context;
  tag_t tag;
  int rc;

  if(fd<0){
    printf("Error: could not create socket %d", fd);
    exit(-1);
  }

  tag = ifc_create_tag(&context);
  ifc_add_integrity(&context, tag);

  printf("PID: %u\n", pid);
  rpid = ifc_start_bridge(IFC_LOGGER_BRIDGE_PATH, FILE_PATH);
  if(rpid<0){
    printf("Error starting bridge.\n");
  }
  printf("Remote PID: %u\n", rpid);
  sleep(1);

  rc = socket(AF_INET, SOCK_STREAM, 0);
  if(rc<0){
    printf("Error opening socket (expected).\n");
  }



  rc = ifc_sendmsg(fd, rpid, TEST_MSG, strlen(TEST_MSG), 0);
  if(rc<0){
    printf("Error sending message %d.\n", rc);
  }
  rc = ifc_sendmsg(fd, rpid, TEST_MSG2, strlen(TEST_MSG2), 0);
  if(rc<0){
    printf("Error sending message %d.\n", rc);
  }
  rc = ifc_sendmsg(fd, rpid, TEST_MSG3, strlen(TEST_MSG3), 0);
  if(rc<0){
    printf("Error sending message %d.\n", rc);
  }

  close(fd);

  return 0;
}
