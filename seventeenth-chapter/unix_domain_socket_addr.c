//
// Created by 王勇椿 on 2020/10/14.
//
//给unix域套接字绑定一个地址时，系统会用该路径名创建一个S_IFSOCK类型的文件，这个只是用来告诉客户进程套接字名字，这个文件无法打开打开，也不能用于应用程序通信
//当绑定的是同一个地址时，这个文件已经存在，bind请求就会失败
#include "../include/apue.h"
#include <sys/socket.h>
#include <sys/un.h>

int
main(void){

    int fd, size;
    struct sockaddr_un un;

    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, "foo.socket");
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){
        err_sys("socket failed");
    }
    //确定绑定地址长度的方法是:先计算sun_path字段在结构中的偏移量，再加上路径名的长度
    size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
    if (bind(fd, (struct sockaddr *)&un, size) < 0){
        err_sys("bind failed");
    }
    printf("UNIX domain socket bound\n");
    exit(0);
}

