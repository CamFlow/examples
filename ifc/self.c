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
  ifc_get_context(&context);
  ifc_context_print(&context);
  return 0;
}
