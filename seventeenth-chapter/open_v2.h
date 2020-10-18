//
// Created by 王勇椿 on 2020/10/18.
//

#ifndef UNIX_ADVANCED_PROGRAMING_OPEN_V2_H
#define UNIX_ADVANCED_PROGRAMING_OPEN_V2_H

//open服务进程第二版(守护进程方式的open服务器进程，一个服务器进程处理所有客户端请求，客户进程和服务器进程还是使用unix域套接字连接)的客户进程
#include "../include/apue.h"

#define CS_OPEN "/tmp/opend.socket"  //server's well-known name
#define CL_OPEN "open"
int csopen_v2(char *, int);

#endif //UNIX_ADVANCED_PROGRAMING_OPEN_V2_H
