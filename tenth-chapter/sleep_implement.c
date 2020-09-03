//
// Created by 王勇椿 on 2020/9/3.
//
//POSIX.1 sleep函数的实现:可靠地处理信号，避免了早期实现中的竞争条件，但是

#include "sleep_implement.h"
#include "../include/apue.h"

static void sig_alarm(int);

unsigned int mysleep(unsigned int seconds){

    struct sigaction newact, oldact;
    sigset_t newmask, oldmask, suspmask;
    unsigned int unslept;

#ifdef LINUX
    newact.sa_handler = sig_alarm;
#elif defined(MACOS)
    newact.__sigaction_u.__sa_handler = sig_alarm;
#endif
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGALRM, &newact, &oldact);

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGALRM);
    sigprocmask(SIG_BLOCK, &newmask, &oldmask);


    alarm(seconds);
    suspmask = oldmask;

    // make sure SIGALRM isn't blocked
    sigdelset(&suspmask, SIGALRM);

    //wait for any signal to be caught
    sigsuspend(&suspmask);

    //some signal has been caught, SIGALRM is now blocked
    unslept = alarm(0);

    //reset previous action
    sigaction(SIGALRM, &oldact, NULL);
    //reset signal mask, which unblocks SIGALRM
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
    return unslept;
}

static void sig_alarm(int signo){

    //nothing to do, just returning wakes up suspend
}


