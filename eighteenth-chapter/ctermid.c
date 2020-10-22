//
// Created by 王勇椿 on 2020/10/21.
//
//ctermid函数获取控制终端的名字。在大多数unix系统上，控制终端的名字一直都是/dev/tty，所以ctermid函数的主要作用是改善向其他操作系统的可移植性
#include <stdio.h>
#include "../include/apue.h"

int
main(void){

    char *ptr;

    if ((ptr = ctermid(NULL)) == NULL){
        err_sys("ctermid error");
    }

    printf("control terminal name: %s", ptr);
}

