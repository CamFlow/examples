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
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "ifclib.h"

#define STRING "we wrote something!"

int main(void){
  pid_t pid = getpid();
  char name[256];
  struct ifc_context context;
  tag_t tag;
  void* map;
  int f;

  tag = ifc_create_tag(&context);
  ifc_add_integrity(&context, tag);
  ifc_context_print(&context);
  sprintf(name, "./test-%d.tmp", pid);
  f = open(name, O_RDWR | O_CREAT);
  write(f, STRING, strlen(STRING));
  printf("Try: camflow-ifc -f ./test-%d.tmp\n", pid);
  map = mmap(0, 40, PROT_READ, MAP_SHARED, f, 0);
  if (map == MAP_FAILED){
    perror("mmap failed");
    exit(-1);
  }
  munmap(map, 40);
  tag = ifc_create_tag(&context);
  ifc_add_integrity(&context, tag);
  map = mmap(0, 40, PROT_READ, MAP_SHARED, f, 0);
  if (map == MAP_FAILED){
    perror("mmap failed (expected)");
    exit(-1);
  }
  close(f);
  return 0;
}
