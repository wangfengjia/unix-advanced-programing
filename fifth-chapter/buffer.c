//
// Created by 王勇椿 on 2020/8/14.
//
//标准I/O缓冲
#include "../include/apue.h"

int main(void){

    FILE *file;
    if ((file = fopen("../file/rename.txt", "r")) == NULL){
        err_sys("open stream error");
    }

    //设置流的缓冲类型
    char buffer[BUFSIZ];
    if (setvbuf(file, buffer, _IOFBF, BUFSIZ) != 0){
        err_sys("setvbuf error");
    }

    exit(0);
}

