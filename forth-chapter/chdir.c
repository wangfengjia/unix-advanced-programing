//
// Created by 王勇椿 on 2020/8/13.
//
//更改进程的当前工作目录

#include <fcntl.h>
#include "../include/apue.h"

#define CONTENT_LENGTH 10

int main(void){

    int fd;
    if ((fd = open("../file/rename.txt", O_RDWR)) < 0){
        err_sys("open file error");
    }

    char content[CONTENT_LENGTH];
    if (read(fd, content, CONTENT_LENGTH) == -1){
        err_sys("read file error");
    }
    printf("content: %s\n", content);
    if (chdir("../file/") < 0){
        err_sys("chdir failed");
    }

    int newfd;
    char new_content[CONTENT_LENGTH];
    if ((newfd = open("./rename.txt", O_RDWR)) < 0){
        err_sys("second open file error");
    }
    if (read(newfd, new_content, CONTENT_LENGTH) < 0){
        err_sys("read content error");
    }
    printf("content: %s\n", new_content);

    printf("chdir succeeded\n");
    exit(0);
}