//
// Created by 王勇椿 on 2020/9/3.
//
#include "mysystem.h"
#include "../include/apue.h"

static void mysig_int(int);
static void mysig_chld(int);

int main(void){

    if (signal(SIGINT, mysig_int) == SIG_ERR){
        err_sys("signal(SIGINT) error");
    }
    if (signal(SIGCHLD, mysig_chld) == SIG_ERR){
        err_sys("signal(SIGCHLD) error");
    }

    if (mysystem("/bin/ed") < 0){
        err_sys("mysystem() error");
    }

    exit(0);
}
static void mysig_int(int signo){

    printf("caught SIGINT\n");
}

static void mysig_chld(int signo){
    printf("caught SIGCHLD\n");
}

