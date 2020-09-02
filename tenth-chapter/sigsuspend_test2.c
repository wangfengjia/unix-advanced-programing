//
// Created by 王勇椿 on 2020/9/2.
//
//sigsuspend函数的另外一个应用是等待一个信号处理程序设置全局变量

#include "../include/apue.h"

volatile sig_atomic_t quitflag;
static void signal_int(int);

int main(void){

    sigset_t newmask, oldmask, zeromask;

    if (signal(SIGINT, signal_int) == SIG_ERR){
        err_sys("signal(SIGINT) error");
    }
    if (signal(SIGQUIT, signal_int) == SIG_ERR){
        err_sys("signal(SIGQUIT) error");
    }

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);

    //block SIGQUIT and save current signal mask
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
        err_sys("SIG_BLOCK error");
    }

    while (quitflag == 0){
        sigsuspend(&zeromask);
    }


    //SIGQUIT has been caught and is now blocked; do whatever
    quitflag = 0;

    //reset signal mask whick unblock SIGQUIT
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        err_sys("SIG_SETMASK error");
    }

    exit(0);
}

static void signal_int(int signo){

    pr_mask("\nin sig_int:\n");
    if (signo == SIGINT){
        printf("\ninterrupt\n");
    } else if (signo == SIGQUIT){
        quitflag = 1;
    }
}