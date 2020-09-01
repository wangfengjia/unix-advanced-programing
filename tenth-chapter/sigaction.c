//
// Created by 王勇椿 on 2020/9/1.
//
//使用sigaction 实现signal函数
#include "../include/apue.h"
#include "mysignal.h"

Sigfunc *mysignal(int signo, Sigfunc *sigfunc){

    struct sigaction act, oldact;

    act.__sigaction_u.__sa_handler = sigfunc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM){
#ifdef SA_INTERRUPT
        act.sa_flag |= SA_INTERRUPT;
#endif
    } else{
        act.sa_flags |= SA_RESTART;
    }

    if (sigaction(signo, &act, &oldact) < 0){
        return SIG_ERR;
    }

    return oldact.__sigaction_u.__sa_handler;
}

Sigfunc *mysignal_v2(int signo, Sigfunc *sigfunc){

    struct sigaction act, oldact;
    act.__sigaction_u.__sa_handler = sigfunc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
#ifdef SA_INTERRUPT
    act.sa_flags |= SA_INTERRUPT;
#endif
    if (sigaction(signo, &act, &oldact) < 0){
        return SIG_ERR;
    }

    return oldact.__sigaction_u.__sa_handler;
}

