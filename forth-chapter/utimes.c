//
// Created by 王勇椿 on 2020/8/13.
//
//将文件长度截断为0，并且不修改文件的访问和修改时间

#include <sys/stat.h>
#include <fcntl.h>
#include "../include/apue.h"


int main(int argc, char *argv[]){

    int i,fd;
    struct stat64 statbuf;
    struct timespec times[2];

    for (i = 1; i < argc; i++){

        if (stat64(argv[i], &statbuf) < 0){
            err_ret("%s: stat error", argv[i]);
            continue;
        }

        //截断文件
        if ((fd = open(argv[1], O_RDWR | O_TRUNC)) < 0){
            err_ret("%s: open error", argv[1]);
            continue;
        }

        times[0] = statbuf.st_atimespec;
        times[1] = statbuf.st_mtimespec;
        if (futimens(fd, times) < 0){
            err_ret("%s: futimens error", argv[i]);
        }

        close(fd);
    }
    exit(0);
}
