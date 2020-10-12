//
// Created by 王勇椿 on 2020/10/12.
//
//如果是面向连接的网络服务，在交换数据之前，客户端套接字和服务器套接字之间需要先建立一个连接。建立连接的过程是:客户端调用connect函数，
// 服务器端先调用listen函数，表示它愿意接收连接请求(也就是监听端口),然后调用accept函数获取连接请求建立连接
//例子:分配和初始化套接字给服务器使用的函数
#include "../include/apue.h"
#include <errno.h>
#include <sys/socket.h>

int initserver(int, const struct sockaddr *, socklen_t alen, int qlen);

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