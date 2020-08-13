//
// Created by 王勇椿 on 2020/8/11.
//

#include "../include/apue.h"
//chmod相关函数，作用是更改现有文件的访问权限

int main(void){

    struct stat statbuf;
    if (stat("../file/foo.txt", &statbuf) < 0){
        err_sys("stat error for foo");
    }

    if (chmod("../file/foo.txt", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0){
        err_sys("chmod error for foo");
    }

    if (chmod("../file/bar.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0){
        err_sys("chmod error for bar");
    }

    exit(0);
}

