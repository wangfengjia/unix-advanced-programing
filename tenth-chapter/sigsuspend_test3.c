//
// Created by 王勇椿 on 2020/9/2.
//
//用信号实现父子进程之间的同步

#include "../include/apue.h"

static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int);
void MY_TELL_WAIT(void);
void MY_TELL_PARENT(pid_t pid);
void MY_WAIT_PARENT(void);
void MY_TELL_CHILD(pid_t pid);
void MY_WAIT_CHILD(void);


static void sig_usr(int signo){
    sigflag = 1;
}

void MY_TELL_WAIT(void){

    if (signal(SIGUSR1, sig_usr) == SIG_ERR){
        err_sys("signal(SIGUSR1) error");
    }

    if (signal(SIGUSR2, sig_usr) == SIG_ERR){
        err_sys("signal(SIGUSR2) error");
    }
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
        err_sys("SIG_BLOCK error");
    }
}

void MY_TELL_PARENT(pid_t pid){

    //tell parent process we are done
    kill(pid, SIGUSR2);
}

void MY_WAIT_PARENT(void){

    while (sigflag == 0){
        //wait for parent
        sigsuspend(&zeromask);
    }

    sigflag = 0;
    //reset signal mask to original value
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        err_sys("SIG_SETMASK error");
    }
}
void MY_TELL_CHILD(pid_t pid){

    //tell child process we are done
    kill(pid, SIGUSR1);
}

void MY_WAIT_CHILD(void){

    while (sigflag == 0){
        //wait for child
        sigsuspend(&zeromask);
    }
    sigflag = 0;
    //reset signal mask to original value
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        err_sys("SIG_SETMASK error");
    }
}


