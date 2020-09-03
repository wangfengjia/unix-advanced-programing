//
// Created by 王勇椿 on 2020/9/3.
//
#include <time.h>
#include "../include/apue.h"

static void mysig_int(int);
static void mysig_usr1(int);

int main(void){

    struct timespec reqtp;
    struct timespec remtp;

    if (signal(SIGINT, mysig_int) == SIG_ERR){
        err_sys("signal(SIGINT) error");
    }
    if (signal(SIGUSR1, mysig_usr1) == SIG_ERR){
        err_sys("signal(SIGUSR1) error");
    }

    reqtp.tv_sec = 10;
    reqtp.tv_nsec = 0;
    if (nanosleep(&reqtp, &remtp) < 0){
        printf("seconds: %ld\n", remtp.tv_sec);
        err_sys("nanosleep() error");
    }
}

static void mysig_int(int signo){

    printf("caught SIGINT\n");
}

static void mysig_usr1(int signal){
    printf("caught SIGUSR1");
}

