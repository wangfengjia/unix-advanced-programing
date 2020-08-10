//
// Created by 王勇椿 on 2020/8/10.
//
//有名字为/dev/fd的目录，包含名字为0，1，2等的文件，打开文件/dev/fc/n相当于复制文件描述符n
//open("/dev/fc/n",mode) 等效于dup(n)

#include "../include/apue.h"
#include <fcntl.h>

int main(void){

    int fd;
    open("/dev/fd/0", O_RDONLY);
}
