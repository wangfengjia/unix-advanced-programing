//
// Created by 王勇椿 on 2020/8/13.
//

//文件的三个时间，文件数据最后访问时间st_atim(read)，文件数据的最后修改时间st_mtim(write),文件的i节点的状态更改时间st_ctim(chown, chowd)
#include <fcntl.h>
#include "../include/apue.h"

#define BUFFER_SIZE 5

void operate_file(){

}

int main(void){

    int fd;
    if ((fd = open("../file/rename.txt", O_RDWR)) < 0){
        err_sys("open file error");
    }

    struct stat buf;
    if (fstat(fd, &buf) < 0){
        err_sys("fstat error");
    }

    printf("st_atim: %ld, st_mtim: %ld, st_ctim:%ld\n", buf.st_atimensec, buf.st_mtimensec, buf.st_ctimensec);

//    char write_con[BUFFER_SIZE] = "sdsdX";
//    if (write(fd, write_con, BUFFER_SIZE) != BUFFER_SIZE){
//        err_sys("write error");
//    }



    if (chmod("../file/rename.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0){
        err_sys("chmod error");
    }

    struct stat buf1;
    if (fstat(fd, &buf1) < 0){
        err_sys("fstat error");
    }
    printf("st_atim: %ld, st_mtim: %ld, st_ctim:%ld\n", buf1.st_atimensec, buf1.st_mtimensec, buf1.st_ctimensec);

}

