//
// Created by 王勇椿 on 2020/9/3.
//
#include "../include/apue.h"
#include "./sleep_implement.h"

static void mysig_int(int);

int main(void){

    if (signal(SIGINT, mysig_int) == SIG_ERR){
        err_sys("signal(SIGINT) error");
    }
    if (mysleep(5) < 0){
        err_sys("mysleep() error");
    }
}

static void mysig_int(int signalno){
    printf("caught SIG_INT\n");
}

