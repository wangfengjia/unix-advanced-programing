//
// Created by 王勇椿 on 2020/10/12.
//

#ifndef UNIX_ADVANCED_PROGRAMING_SOCKET_LIB_H
#define UNIX_ADVANCED_PROGRAMING_SOCKET_LIB_H

#include <sys/socket.h>

#define MAXSLEEP 128

int connect_retry(int, int, int, const struct sockaddr *, socklen_t);
int initserver(int, const struct sockaddr *, socklen_t, int);
int initserver_v2(int, const struct sockaddr *, socklen_t, int);

//创建一对相互连接的unix域流套接字
int my_fd_pipe(int fd[2]);
#endif //UNIX_ADVANCED_PROGRAMING_SOCKET_LIB_H
