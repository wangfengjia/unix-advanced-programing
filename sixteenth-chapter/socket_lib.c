//
// Created by 王勇椿 on 2020/10/12.
//
#include "../include/apue.h"
#include "socket_lib.h"
#include <errno.h>
#include <sys/socket.h>


int
connect_retry(int domain, int type, int protocol, const struct sockaddr *addr, socklen_t len){

    int numsec, fd;

    //Try to connect with exponential backoff
    // (指数补偿算法:调用connect失败，进程会休眠一段时间，然后进入下次循环再次尝试，休眠时间以指数级增长，直到最大延迟时间)
    for (numsec = 1; numsec <= MAXSLEEP; numsec <<= 1){
        if ((fd = socket(domain, type, protocol)) < 0){
            return (-1);
        }

        if (connect(fd, addr, len) == 0){
            return (fd);
        }
        close(fd);

        //失败时，进程休眠一段时间
        if (numsec <= MAXSLEEP / 2){
            sleep(numsec);
        }
    }

    return (-1);
}

int
initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen){

    int fd;
    int err = 0;
    errno = 0;

    if ((fd = socket(addr->sa_family, type, 0)) < 0){
        return (-1);
    }
    if (bind(fd, addr, alen) < 0){
        goto errout;
    }
    if (type == SOCK_STREAM || type == SOCK_SEQPACKET){
        if (listen(fd, qlen) < 0){
            goto errout;
        }
    }

    return (fd);

    errout:
    err = errno;
    close(fd);
    errno = err;
    return (-1);
}

//TCP的实现不允许绑定同一个地址，可以通过套接字选项SO_REUSEADDR来绕过这个限制
int
initserver_v2(int type, const struct sockaddr *addr, socklen_t alen, int qlen){

    int fd;
    int err = 0;
    int reuse = 1;

    if ((fd = socket(addr->sa_family, type, 0)) < 0){
        return (-1);
    }
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0){
        goto errout;
    }
    if (bind(fd, addr, alen) < 0){
        goto errout;
    }
    if (type == SOCK_STREAM || type == SOCK_SEQPACKET){
        if (listen(fd, qlen) < 0){
            goto errout;
        }
    }

    return (fd);

    errout:
        err = errno;
        close(fd);
        errno = err;
        return (-1);
}


int
my_fd_pipe(int fd[2]){

    return (socketpair(AF_UNIX, SOCK_STREAM, 0, fd));
}


























