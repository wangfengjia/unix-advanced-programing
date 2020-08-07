//
// Created by 王勇椿 on 2020/8/6.
//

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../include/apue.h"


void l_open_openat(void);
void l_creat(void);
void l_lseek(void);
void make_cavity_file(void); //创建有空洞的文件
void l_read(void);
void l_write(void);


int main(void){

//    l_open_openat();
//    l_creat();
//    l_lseek();
//    make_cavity_file();
//    l_read();
    l_write();
}

void l_open_openat(void){

    char *file_path = "../file/sys_limit.txt";
    char *dir_name = "../file/";

    errno = 0;
//    int descriptor = open(file_path, O_DIRECTORY);
//    if (errno != 0){
////        printf("open failed\n");
//        perror("open filed");
//        puts(strerror(errno));
//    }

    int fd = open("../file/", O_DIRECTORY);
    openat(fd, "../file/sys_limit.txt", O_RDONLY);

    if (errno != 0){

        perror("openat error: ");
    }
}

void l_creat(void){

    creat("../file/creat.txt", 21);
}

void l_lseek(void){

    int fd = open("../file/sys_limit.txt", O_WRONLY);

    //利用lseek函数来确定打开文件的当前偏移量
    off_t current_pos = lseek(fd, 0, SEEK_CUR);
    printf("file current pos: %lld\n", current_pos);
    lseek(fd, 2, SEEK_CUR);
    current_pos = lseek(fd, 0, SEEK_CUR);
    printf("file current pos: %lld\n", current_pos);

    //确定标准输入能否设置文件偏移量
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1){
        printf("stdin can not set file pos\n");
    } else{
        printf("stdin can set file pos\n");
    }
}

void make_cavity_file(void){

    char buf1[] = "abcdefghij";
    char buf2[] = "ABCDEFGHIJ";

    int fd;

    if ((fd = creat("../file/cavity.txt", FILE_MODE)) < 0){
        err_sys("creat error");
    }

    if (write(fd, buf1, 10) != 10){
        err_sys("buf1 write error");
    }

    if (lseek(fd, 16384, SEEK_SET) == -1){
        err_sys("lseek error");
    }

    if (write(fd, buf2, 10) != 10){
        err_sys("buf2 write error");
    }
}

void l_read(void){

    int fd;
    if ((fd = open("../file/sys_limit.txt", O_RDONLY)) < 0){
        err_sys("open file error");
    }

    size_t bytes = 5;
    char buf[bytes];

    //fd只能用只读的方式打开文件
    if (read(fd, buf, bytes) == -1){
        err_sys("read error");
    }

    printf("content: %s\n", buf);

}

void l_write(void){

    int fd;
    //追加写
    if ((fd = open("../file/sys_limit.txt", O_WRONLY)) < 0){
        err_sys("open file error");
    }

//    if (lseek(fd, 20, SEEK_SET) == -1){
//        err_sys("lseek error");
//    }

    char buf[] = "jetbrain idea";
    size_t bytes = sizeof(buf);
    if (write(fd, buf, bytes) == -1){
        err_sys("write error");
    }
}