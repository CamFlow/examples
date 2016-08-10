#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provenancelib.h"
#include "provenancePovJSON.h"

prov_identifier_t last;
prov_identifier_t current;

int cp(const char *to, const char *from)
{
    int fd_to, fd_from;
    char buf[4096];
    ssize_t nread;
    int saved_errno;

    disclose_activity_ProvJSON("\"rdt:name\":\"fd_from = open(from, O_RDONLY);\", \"rdt:scriptLine\":\"22\"", &current);
    fd_from = open(from, O_RDONLY);


    if (fd_from < 0)
        return -1;

    disclose_activity_ProvJSON("\"rdt:name\":\"fd_to = open(to, O_WRONLY | O_CREAT | O_EXCL, 0666);\", \"rdt:scriptLine\":\"29\"", &current);
    fd_to = open(to, O_WRONLY | O_CREAT | O_EXCL, 0666);
    if (fd_to < 0)
        goto out_error;

    while (nread = read(fd_from, buf, sizeof buf), nread > 0)
    {
        disclose_activity_ProvJSON("\"rdt:name\":\"while (nread = read(fd_from, buf, sizeof buf), nread > 0)\", \"rdt:scriptLine\":\"36\"", &current);
        char *out_ptr = buf;
        ssize_t nwritten;

        do {
            disclose_activity_ProvJSON("\"rdt:name\":\"nwritten = write(fd_to, out_ptr, nread);\", \"rdt:scriptLine\":\"40\"", &current);
            nwritten = write(fd_to, out_ptr, nread);

            if (nwritten >= 0)
            {
                nread -= nwritten;
                out_ptr += nwritten;
            }
            else if (errno != EINTR)
            {
                goto out_error;
            }
        } while (nread > 0);
    }

    if (nread == 0)
    {
        if (close(fd_to) < 0)
        {
            fd_to = -1;
            goto out_error;
        }
        close(fd_from);

        /* Success! */
        return 0;
    }

  out_error:
    saved_errno = errno;

    close(fd_from);
    if (fd_to >= 0)
        close(fd_to);

    errno = saved_errno;
    return -1;
}

int main(){
  if(provenance_set_tracked(true)){
    printf("Failed Tracking, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
  }
  if(cp("./test/output.txt", "./test/input.txt")){
    printf("Failed copying, error %d\n", errno);
    printf("%s\n\n",strerror(errno));
  }
}
