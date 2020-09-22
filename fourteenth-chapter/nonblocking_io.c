//
// Created by 王勇椿 on 2020/9/18.
//
//非阻塞I/O的实例，它从标准输入读500000字节，并试图将它们写到标准输出
#include "../include/apue.h"
#include <errno.h>
#include <fcntl.h>

#define BUFFER_SIZE 500000
char io_buf[BUFFER_SIZE];

int
main(void){

    int ntowrite, nwrite;
    char *ptr;

    ntowrite = read(STDIN_FILENO, io_buf, sizeof(io_buf));
    fprintf(stderr, "read %d bytes\n", ntowrite);

    //set nonblocking
    set_fl(STDOUT_FILENO, O_NONBLOCK);

    ptr = io_buf;
    while (ntowrite > 0){
        errno = 0;
        nwrite = write(STDOUT_FILENO, ptr, ntowrite);
        fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);
        if (nwrite > 0){
            ptr += nwrite;
            ntowrite -= nwrite;
        }
    }

    //clear nonblocking
    clr_fl(STDOUT_FILENO, O_NONBLOCK);
    exit(0);
}



