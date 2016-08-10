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

#include "ifclib.h"

int main(void){
  int rc;
  struct ifc_context context;
  tag_t tag1, tag2;

  printf("Camflow %s\n", CAMFLOW_VERSION_STR);

  tag1 = ifc_create_tag(&context);
  tag2 = ifc_create_tag(&context);

  ifc_context_print(&context);

  rc = ifc_remove_secrecyp(&context, tag1);
  if(rc<0){
    printf("Error remove %d\n", rc);
    exit(-1);
  }
  ifc_remove_secrecyn(&context, tag1);

  ifc_remove_secrecyp(&context, tag2);
  ifc_remove_secrecyn(&context, tag2);

  ifc_context_print(&context);

  rc = ifc_add_integrity(&context, tag1);
  if(rc<0){
    printf("Error %d\n", rc);
    exit(-1);
  }

  rc = ifc_add_secrecy(&context, tag1);
  if(rc<0){
    printf("Error (expected) %d\n", rc);
  }

  rc = ifc_add_integrity(&context, tag2);
  if(rc<0){
    printf("Error %d\n", rc);
    exit(-1);
  }

  ifc_context_print(&context);

  pid_t pid = fork();

  if(pid==0){ // child
    printf("\n\nChild\n");
    ifc_get_context(&context);
    ifc_context_print(&context);
    sleep(2);
    printf("\n\nChild\n");
    ifc_get_context(&context);
    ifc_context_print(&context);
    sleep(5);
  }else if(pid > 0){ // parent
    sleep(1);
    rc = ifc_pass_integrityp(tag1, pid); // pass privilege
    sleep(2);
    if(rc<0){
      printf("Error failed pass %d\n", rc);
      exit(-1);
    }
    rc = ifc_get_other_context(pid, &context);
    if(rc<0){
      printf("Error failed get other %d\n", rc);
      exit(-1);
    }
    printf("\n\nParent read child:\n");
    ifc_context_print(&context);
    sleep(2);
  }else{ // error
    printf("Fork failed\n");
  }

  return 0;
}
