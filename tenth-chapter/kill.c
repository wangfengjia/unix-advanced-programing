//
// Created by 王勇椿 on 2020/8/29.
//
#include "../include/apue.h"
#include <signal.h>

static void sig_stop(int);

int main(void){

    pid_t pid;
    if (signal(SIGABRT, sig_stop) == SIG_ERR){
        perror("signal error");
    }

    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid == 0){
        printf("child process, wait parent process stop");
    } else{
        if (kill(getpid(), SIGABRT) < 0){
            err_sys("kill error");
        }
        printf("parent process id: %ld\n", (long)getpid());
    }

    exit(0);
}

static void sig_stop(int signo){

    printf("process stop, process id: %ld\n", (long)getpid());
    exit(0);
}