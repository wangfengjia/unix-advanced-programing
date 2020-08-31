//
// Created by 王勇椿 on 2020/8/29.
//

//alarm函数设置一个定时器，在将来的某个时刻该定时器会超时。当定时器超时时，产生SIGALARM信号
//pause函数使调用进程挂起直至捕捉到一个信号。只有在执行完一个信号处理程序时，pause函数才返回

#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include "../include/apue.h"

static jmp_buf env_alarm;

static void sig_alarm_v1(int);
static void sig_alarm_v2(int);

unsigned int sleep_v1(int seconds);
unsigned int sleep_v2(int seconds);
int main(void){

    sleep_v2(2);
}

unsigned int sleep_v1(int seconds){

    if (signal(SIGALRM, sig_alarm_v1) == SIG_ERR){
        err_sys("signal error");
    }

    //start the timer
    alarm(seconds);
    pause();
    //turn off the timer,return unslept time
    return (alarm(0));
}
static void sig_alarm_v1(int signo){

    //nothing to do ,just return to wake up the pause
    printf("signal alarm handler\n");
}

//sleep函数的第二个版本，在第一个版本中，第一次调用alarm函数pause之间有一个竞争条件，在一个繁忙的系统中，可能alarm在调用pause函数之前超时
//并且执行了信号处理程序。如果发生了这种情况，则再调用pause函数，如果没有捕捉到其他信号，则调用者则被永远挂起
//解决这个问题的第一个方法是使用setjmp和longjmp函数
//这个函数的一个难以察觉的问题，它涉及与其他信号的交互。如果SIGALARM中断了其他信号处理程序，则调用longjmp会提前终止信号处理程序
unsigned int sleep_v2(int seconds){

    if (signal(SIGALRM, sig_alarm_v2) == SIG_ERR){
        return (seconds);
    }

    if (setjmp(env_alarm) == 0){
        alarm(seconds);
        pause();
    }

    return (alarm(0));
}


static void sig_alarm_v2(int signo){

    printf("sign alarm v2\n");
    longjmp(env_alarm, 1);
}