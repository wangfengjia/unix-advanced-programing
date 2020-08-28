//
// Created by 王勇椿 on 2020/8/27.
//
//SIGCLD信号

#include "../include/apue.h"
#include <sys/wait.h>

static void sig_cld(int);

int main(void){

    pid_t pid;

    if (signal(SIGCHLD, sig_cld) == SIG_ERR){
        perror("signal error");
    }

    if ((pid = fork()) < 0){
        perror("fork error");
    } else if (pid == 0){ //child process
        sleep(2);
        _exit(0);
    }

    //parent process
    pause();
    exit(0);

}

static void sig_cld(int signo){

    pid_t pid;
    int status;

    printf("SIGCLD received\n");

    //重新设置此信号处理程序，要不然信号被捕捉一次后，信号的处理方式会被设置为执行系统默认操作(一般是终止进程)
    //这个程序在某些system V平台上将SIGCLD的配置设置为捕捉时，内核会立即检查是否有子进程准备好被等待，如果有的话，则调用信号处理函数
    //在这里又调用signal函数，内核又会立刻检查是否有子进程准备好被等待，由于我们正在执行信号处理程序处理SIGCLD信号，所以确实有这种的子进程
    //这样就会形成死递归，需要在调用wait取得子进程的状态后再次调用signal函数，此时，仅仅当其他子进程终止时，内核才会再次产生此信号
    if (signal(SIGCHLD, sig_cld) == SIG_ERR){
        perror("signal error");
    }

    //获取子进程状态
    if ((pid = wait(&status)) < 0){
        perror("wait error");
    }

    printf("pid = %d\n", pid);
}

