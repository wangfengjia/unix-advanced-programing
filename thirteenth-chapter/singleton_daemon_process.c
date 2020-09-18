//
// Created by 王勇椿 on 2020/9/17.
//
#include <unistd.h>
#include <stdlib.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/file.h>
#include "singleton_daemon_process.h"
#include "../include/apue.h"

extern int lockfile(int);

int already_running(void){

    int fd;
    char buf[BUFFER_LENGTH];
    int errno;

    errno = 0;
    fd = open(LOCKFILE, O_RDWR | O_CREAT, LOCKMODE);
    if (fd < 0){
        syslog(LOG_ERR, "can't open %s: %s", LOCKFILE, strerror(errno));
    }

    if (lockfile(fd) < 0){
        if (errno == EACCES || errno == EAGAIN){
            close(fd);
            return (1);
        }
        syslog(LOG_ERR, "can't lock %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    }
    ftruncate(fd, 0);
    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf) + 1);
    return 0;
}

