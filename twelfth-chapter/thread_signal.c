//
// Created by 王勇椿 on 2020/9/15.
//
//线程与信号:进程中的信号只递送给单个线程。与硬件故障相关的信号会递送给产生此异常的线程，其他的信号会递送给任意一个线程
//例子:等待信号处理程序设置标志表明主程序应该退出。两个线程:一个主线程，一个信号处理程序线程

#include <pthread.h>
#include <stdbool.h>
#include "../include/apue.h"

int quitflag;
sigset_t mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitloc = PTHREAD_COND_INITIALIZER;

void *thread_function(void *arg);

void *thread_function(void *arg){

    int err, signo;

    while (true){
        //sigwait函数会解除对mask信号集的阻塞
        err = sigwait(&mask, &signo);
        if (err != 0){
            err_exit(err, "sigwait failed");
        }

        switch (signo) {
            case SIGINT:
                printf("\ninterrupt\n");
                break;
            case SIGQUIT:
                pthread_mutex_lock(&lock);
                quitflag = 1;
                pthread_mutex_unlock(&lock);
                pthread_cond_signal(&waitloc);
                return 0;
            default:
                printf("unexpected signal %d\n", signo);
                exit(1);
        }
    }
}

int main(void){

    int err;
    sigset_t oldmask;
    pthread_t tid;

    //线程屏蔽阻塞这几个信号(线程完成sigwait调用之前会有一段时间窗口，在这个时间窗口中，信号就有可能递送给主线程)，
    // 不依赖信号处理程序中断主线程，有专门的独立线程进行信号处理
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);

    if ((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0){
        err_exit(err, "SIG_BLOCK error");
    }

    //新线程会继承主线程的信号屏蔽字
    err = pthread_create(&tid, NULL, thread_function, 0);
    if (err != 0){
        err_exit(err, "can't create thread");
    }

    pthread_mutex_lock(&lock);
    while (quitflag == 0){
        pthread_cond_wait(&waitloc, &lock);
    }
    pthread_mutex_unlock(&lock);

    //SIGQUIT has been caught and now is blocked;do whatever
    quitflag = 0;

    //reset signal mask which unblocks SIGQUIT
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        err_sys("SIG_SETMASK error");
    }

    exit(0);
}


