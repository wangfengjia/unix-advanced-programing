//
// Created by 王勇椿 on 2020/8/29.
//

//alarm函数设置一个定时器，在将来的某个时刻该定时器会超时。当定时器超时时，产生SIGALARM信号
//pause函数使调用进程挂起直至捕捉到一个信号。只有在执行完一个信号处理程序时，pause函数才返回

#include <unistd.h>
#include <signal.h>
#include "../include/apue.h"

static void sig_alarm(int);

static void sleep_v1(int seconds);
static void sleep_v2(int seconds);
int main(void){

    int seconds = 3;
    if (signal(SIGALRM, sig_alarm) == SIG_ERR){

        err_sys("signal error");
    }

    //start the timer
    alarm(seconds);
    pause();
    //turn off the timer,return unslept time
    return (alarm(0));
}

static void sig_alarm(int signo){

    //nothing to do ,just return to wake up the pause
    printf("signal alarm handler\n");
}