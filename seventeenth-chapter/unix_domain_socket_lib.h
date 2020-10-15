//
// Created by 王勇椿 on 2020/10/14.
//

#ifndef UNIX_ADVANCED_PROGRAMING_UNIX_DOMAIN_SOCKET_LIB_H
#define UNIX_ADVANCED_PROGRAMING_UNIX_DOMAIN_SOCKET_LIB_H
/**
 * 服务器进程可以使用标准bind、listen和accept函数，为客户进程提供一个唯一unix域连接。客户进程使用connect与服务器进程联系，在服务器进程接受了connect
 * 请求后，在服务器进程和客户进程之间就存在唯一连接，一下三个函数就是为了实现这个功能:为运行与同一台计算机上的两个无关进程创建唯一连接
 */
#include "../include/apue.h"

//服务器进程声明在一个众所周知的名字(文件系统上的某个路径名)上监听客户端连接请求，返回值是用于接收客户端连接请求的服务器unix域套接字
int server_listen(const char *);
//等待客户端连接请求的到来，客户端连接请求到来以后，获取客户端连接请求，自动创建一个新的unix域套接字，并与客户端套接字建立练剑，最后将新的套接字返回给服务器
int server_accept(int listenfd, uid_t *);
//客户进程调用此函数连接到服务器进程。返回值是连接到服务器进程的文件描述符
int client_connect(const char *);
#endif //UNIX_ADVANCED_PROGRAMING_UNIX_DOMAIN_SOCKET_LIB_H
