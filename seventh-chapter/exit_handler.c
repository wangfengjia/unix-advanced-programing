//
// Created by 王勇椿 on 2020/8/16.
//
//进程终止处理程序

#include "../include/apue.h"

static void my_exit1(void);
static void my_exit2(void);


int main(void){

    if (atexit(my_exit2) != 0){
        err_sys("can't register my_exit2");
    }

    //进程处理函数每登记一次，就会被调用一次，即使是相同的函数，先登记的后执行
    if (atexit(my_exit1) != 0){
        err_sys("can't register my_exit1");
    }

    if (atexit(my_exit1) != 0){
        err_sys("can't register my_exit1");
    }

    printf("main is done\n");
//    exit(0);
    return 0;
}


static void my_exit1(void){

    printf("first exit handler\n");
}

static void my_exit2(void){
    printf("second exit handler\n");
}

