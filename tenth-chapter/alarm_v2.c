//
// Created by 王勇椿 on 2020/8/31.
//

#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include "../include/apue.h"

static jmp_buf env_alarm;

//这个函数有一个难以察觉的问题，它涉及信号交互，如果SIGALRM中断了其他的信号处理程序，则调用longjmp会提前终止该信号处理程序
unsigned int mysleep(int);
static void sig_alarm(int);
static void sig_int(int);


int main(void){

    unsigned int unslept;
    if (signal(SIGINT, sig_int) == SIG_ERR){
        err_sys("signal error");
    }

    unslept = mysleep(2);
    printf("sleep returned: %u\n", unslept);
    exit(0);
}

static void sig_int(int signo){

    int i, j;
    volatile int k;

    printf("\nsig_int starting\n");
    for (i = 0; i < 3000000; i++){
        for (j = 0; j < 4000; j++){
            k += i * j;
        }
    }
    printf("sig_int finished \n");
}
unsigned int mysleep(int seconds){

    if (signal(SIGALRM, sig_alarm) == SIG_ERR){
        err_sys("signal error");
    }

    if (setjmp(env_alarm) == 0){
        alarm(seconds);
        pause();
    }

    return (alarm(0));
}

static void sig_alarm(int signo){

//    printf("signal alarm");
    longjmp(env_alarm, 1);
}

