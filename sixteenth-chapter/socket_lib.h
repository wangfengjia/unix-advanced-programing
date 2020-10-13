//
// Created by 王勇椿 on 2020/10/12.
//

#ifndef UNIX_ADVANCED_PROGRAMING_SOCKET_LIB_H
#define UNIX_ADVANCED_PROGRAMING_SOCKET_LIB_H

#include <sys/socket.h>

#define MAXSLEEP 128

int connect_retry(int, int, int, const struct sockaddr *, socklen_t);
int initserver(int, const struct sockaddr *, socklen_t alen, int qlen);
#endif //UNIX_ADVANCED_PROGRAMING_SOCKET_LIB_H
