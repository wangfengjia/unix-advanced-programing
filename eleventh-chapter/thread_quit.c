//
// Created by 王勇椿 on 2020/9/5.
//
//线程终止，在不终止进程的情况下，线程终止的三种方式
//1.线程可以简单地从启动例程返回，返回值是线程的退出码
//2.线程可以被同一个进程的其他线程取消
//3.线程pthread_quit函数

//可以通过pthread_join函数等待一个指定线程终止，并获取线程的返回值
//例子:获取已终止线程的退出码

#include <pthread.h>
#include "../include/apue.h"

void *thr_fn1(void *args);
void *thr_fn2(void *args);

int main(void){

    int err;
    pthread_t td1, td2;
    void *tret;

    err = pthread_create(&td1, NULL, thr_fn1, NULL);
    if (err != 0){
        err_exit(err, "can't create thread 1");
    }
    err = pthread_create(&td2, NULL, thr_fn2, NULL);
    if (err != 0){
        err_exit(err, "can't create thread2");
    }

    err = pthread_join(td1, &tret);
    if (err != 0){
        err_exit(err, "can't join thread 1");
    }
    printf("thread 1 exit code %ld\n", (long)tret);
    err = pthread_join(td2, &tret);
    if (err != 0){
        err_exit(err, "can't join thread 2");
    }
    printf("thread 2 exit code %ld\n", (long)tret);
    exit(0);
}
void *thr_fn1(void *args){

    printf("thread 1 returning\n");
    return (void *)1;
}

void *thr_fn2(void *args){
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

