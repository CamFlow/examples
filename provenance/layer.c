#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provenance.h"

int main( void ){
  int rc;
  int a; entity_t prov_a;
  int b; entity_t prov_b;
  int fin; entity_t prov_fin;
  activity_t activity1, activity2;

  if(provenance_set_tracked(true)){
    printf("Failed Tracking, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
    return -1;
  }

  if (disclose_init() != 0) {
    printf("Failed initialising disclosing framework\n");
    return -1;
  }

  fin = open("/tmp/in", O_CREAT|O_RDWR);

  // disclose a
  prov_a = disclose_entity("\"prov:label\":\"a\"");
  // disclose b
  prov_b = disclose_entity("\"prov:label\":\"b\"");


  a = b;
  // disclose activity
  activity1 = disclose_activity("\"prov:label\":\"a = b;\"");
  disclose_uses(prov_a, activity1);
  disclose_generates(activity1, prov_b);

  write(fin, &b, sizeof(int));
  activity2 = disclose_activity("\"prov:label\":\"write(fin, &b, sizeof(int));\"");
  prov_fin = disclose_get_file("/tmp/in");
  disclose_informs(activity1, activity2);
  disclose_uses(prov_b, activity2);
  disclose_generates(activity2, prov_fin);
  close(fin);
}
