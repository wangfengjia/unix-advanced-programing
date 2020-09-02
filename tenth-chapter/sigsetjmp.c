//
// Created by 王勇椿 on 2020/9/1.
//
#include "../include/apue.h"
#include <setjmp.h>
#include <time.h>
#include <stdbool.h>

static void sig_usr1(int);
static void sig_alarm(int);
static jmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

int main(void){

    if (signal(SIGUSR1, sig_usr1) == SIG_ERR){
        err_sys("signal(SIGUSR1) error");
    }

    if (signal(SIGALRM, sig_alarm) == SIG_ERR){
        err_sys("signal(SIGALRM) error");
    }

    pr_mask("starting main: ");
    if (sigsetjmp(jmpbuf, 1)){
        pr_mask("ending main");
        exit(0);
    }
    canjump = 1;
    while (true){
        pause();
    }
}

static void sig_usr1(int signo){

    time_t starttime;

    //我们想在jmpbuf由sigsetjmp函数初始化时，才会调用信号处理程序
    if (canjump == 0){
        return;
    }

    pr_mask("starting sig_usr1: ");

    alarm(3);
    starttime = time(NULL);

    while (true){

        if (time(NULL) > starttime + 5){
            break;
        }
    }
    pr_mask("finishing sig_usr1: ");
    canjump = 0;

    //jump back to main, don't return
    siglongjmp(jmpbuf, 1);
}

static void sig_alarm(int signo){
    pr_mask("in sig_alrm: ");
}

