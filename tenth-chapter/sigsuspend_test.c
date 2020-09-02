//
// Created by 王勇椿 on 2020/9/1.
//

//当有这么一种需求时:先设置对一个信号阻塞，然后解除对这个信号的阻塞，再用pause已等待以前被阻塞的信号发生
//这个时候就可以使用sigsuspend函数
//sigsuspend函数:进程的信号屏蔽字设置为由sigmask参数的值，这样就可以指定不捕捉特定的信号，
//              在捕捉到一个信号或者发生一个会终止该进程的信号前，进程会被挂起，如果捕捉到一个信号然后从信号处理程序返回时
//              则sigsuspeng函数返回，会将进程的信号屏蔽字设置为调用sigsuspeng之前的值

//保护代码临界区，使其不会被特定信号中断的办法

#include "../include/apue.h"

static void suspend_sig_int(int);

int main(void){

    sigset_t newmask, waitmask, oldmask;
    pr_mask("program start");

    if (signal(SIGINT, suspend_sig_int) == SIG_ERR){
        err_sys("signal(SIGINT) error");
    }
    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    //Block SIGINT and save current signal mask
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
        err_sys("SIG_BLOCK error");
    }

    //代码临界区
    pr_mask("in critical region: ");

    //pause,allowing all signals except SIGUSR1
    if (sigsuspend(&waitmask) != -1){
        err_sys("sigsuspend error");
    }

    pr_mask("after return from sigsuspend: ");

    //reset signal mask which unblocks SIGINT
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        err_sys("SIG_SETMASK error");
    }
    pr_mask("program exit: ");
    exit(0);
}

static void suspend_sig_int(int signo){

    pr_mask("\nin sig_int: \n");
}

