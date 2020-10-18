//
// Created by 王勇椿 on 2020/10/17.
//

#ifndef UNIX_ADVANCED_PROGRAMING_OPEN_H
#define UNIX_ADVANCED_PROGRAMING_OPEN_H

//利用文件描述符传送技术开发一个open服务器进程(执行打开一个或者多个文件)，客户进程向服务器进程传送文件名和打开模式，服务器进程向客户进程传送文件描述符
#include "../include/apue.h"
#include <errno.h>

#define CL_OPEN "open"  //client's request for server

int csopen(char *, int);
#endif //UNIX_ADVANCED_PROGRAMING_OPEN_H
