//
// Created by 王勇椿 on 2020/10/18.
//

#ifndef UNIX_ADVANCED_PROGRAMING_OPEND_V2_H
#define UNIX_ADVANCED_PROGRAMING_OPEND_V2_H

//open服务器进程第二版:是一个守护进程，一个服务器进程处理所有客户进程请求，因为要使用到select和poll函数
#include "../include/apue.h"
#include <errno.h>

#define CS_OPEN "/tmp/opend.socket"
#define CL_OPEN "open"

extern int debug;
extern char errmsg_v2[];
extern int oflag_v2;
extern char *pathname_v2;

//one client struct per connected client
typedef struct{
    int fd;
    uid_t uid;
} Client;

extern Client *client;
extern int client_size;

int client_args(int, char **);
int client_add(int, uid_t);
void client_del(int);
void loop(void);
void handle_request_v2(char *, int, int, uid_t);

#endif //UNIX_ADVANCED_PROGRAMING_OPEND_V2_H
