//
// Created by 王勇椿 on 2020/8/13.
//
//创建一个文件或者目录的符号链接

#include <fcntl.h>
#include "../include/apue.h"

void create_link(void);
void read_link(void);

int main(void){

//    create_link();
    read_link();
}

void create_link(void){

    if (symlink("../file/rename.txt", "../file/rename_link") < 0){
        err_sys("symlink error");
    }

    int fd;
    if ((fd = open("../file/", O_DIRECTORY)) < 0){
        err_sys("open file error");
    }

    if (symlinkat("./rename.txt", fd, "./new_link") < 0){
        err_sys("symlink at error");
    }
}

void read_link(void){

    size_t buf_size = 100;
    char buf[buf_size];

    if (readlink("../file/new_link", buf, buf_size) < 0){
        err_sys("read symlink error");
    }

    printf("symlink name: %s\n", buf);
}

