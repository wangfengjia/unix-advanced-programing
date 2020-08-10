//
// Created by 王勇椿 on 2020/8/10.
//

//对一个文件描述符设置一个或者多个文件状态标志

#include "../include/apue.h"
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>

void set_f1(int fd, int flags){

    int val;
    if ((val = fcntl(fd, F_GETFL, 0)) < 0){
        err_sys("fcntl F_GETFL error");
    }

    val |= flags;

    if (fcntl(fd, F_SETFL, val) < 0){
        err_sys("fcntl F_SETFL error");
    }
}