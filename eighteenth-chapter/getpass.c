//
// Created by 王勇椿 on 2020/10/21.
//
//规范模式:发送一个读请求，当一行已经输入时，终端驱动程序返回
#include "../include/apue.h"
#include "terminal_io_lib.h"

int
main(void){

    char *ptr;
    if ((ptr = getpass("Enter password:")) == NULL){
        err_sys("getpass error");
    }
    printf("password: %s\n", ptr);

    //now use password

    while (*ptr != 0){
        *ptr++ = 0; //zero it out when we're done with it
    }
    exit(0);
}

