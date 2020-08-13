//
// Created by 王勇椿 on 2020/8/13.
//
//修改文件数据的最后访问和最后修改时间

#include <sys/stat.h>
#include <fcntl.h>
#include "../include/apue.h"

int main(void){

    struct timespec times[2];

    int fd;
    if ((fd = open("../file/rename.txt", O_RDWR)) < 0){
        err_sys("open file error");
    }

//    if (futimens(fd, NULL) < 0){
//        err_sys("futimens error");
//    }

    times[0].tv_nsec = UTIME_NOW;
    times[1].tv_nsec = UTIME_NOW;
    if (futimens(fd, times) < 0){
        err_sys("futimens error");
    }

}

