//
// Created by 王勇椿 on 2020/8/31.
//
//sigpending函数返回信号集，对于调用进程而言，信号集中的各个信号是阻塞而不能递送的，因此当前也是未决的

#include "../include/apue.h"

static void sig_quit(int);

int main(void){

    sigset_t newmask, oldmask, pendmask;
    if (signal(SIGQUIT, sig_quit) == SIG_ERR){
        err_sys("can't catch SIGQUIT");
    }

    //block sigquit and save current signal mask
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
        err_sys("SIG_BLOCK error");
    }

    sleep(5);
    if (sigpending(&pendmask) < 0){
        err_sys("sigpending error");
    }
    if (sigismember(&pendmask, SIGQUIT)){
        printf("\nSIGQUIT pending\n");
    }

    printf("content middile ware\n");
    //restore signal mask which unblocks SIGQUIT
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        err_sys("SIG_SETMASK error");
    }
    printf("SIGQUIT unblocked\n");
    sleep(5);
    exit(0);
}


static void sig_quit(int signo){

    printf("catch SIGQUIT\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR){
        err_sys("can't reset sigquit");
    }
}



