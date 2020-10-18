//
// Created by 王勇椿 on 2020/10/18.
//

#include "open_v2.h"
#include <sys/uio.h>

int
csopen_v2(char *name, int oflag){

    int len;
    char buf[12];
    struct iovec iov[3];
    static int csfd = -1;

    if (csfd < 0){ // open connection to open server
        if ((csfd = cli_conn(CS_OPEN)) < 0){
            err_ret("cli_conn error");
            return (-1);
        }
    }

    sprintf(buf, " %d", oflag);
    iov[0].iov_base = CL_OPEN "";
    iov[0].iov_len = strlen(CS_OPEN) + 1;
    iov[1].iov_base = name;
    iov[1].iov_len = strlen(name);
    iov[2].iov_base = buf;
    iov[2].iov_len = strlen(buf) + 1;

    len = iov[0].iov_len + iov[1].iov_len + iov[1].iov_len;
    if (writev(csfd, &iov[0], 3) != len){
        err_ret("writev error");
        return (-1);
    }

    return (recv_fd(csfd, write));
}

