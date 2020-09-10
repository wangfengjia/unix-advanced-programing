//
// Created by 王勇椿 on 2020/9/8.
//
//当不需要了解线程的终止状态时，可以在创建线程时修改pthread_attr_t结构的detachstate属性值

//例子:以分离状态创建线程的函数
#include "../include/apue.h"
#include "detach_state.h"
#include <pthread.h>
void *thr_function(void *);

int makethread(void *(*fun)(void *), void *arg){

    int err;
    pthread_attr_t attr;
    pthread_t tid;

    err = pthread_attr_init(&attr);
    if (err != 0){
        return err;
    }
    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (err == 0){
        err = pthread_create(&tid, &attr, fun, arg);
    }
//    err = pthread_create(&tid, NULL, fun, arg);

    pthread_attr_destroy(&attr);
    return err;
}

void *thr_function(void *args){

    int i;
    long sum = 0;
    for (i = 0; i < 1000000; i++){
        sum += i;
    }

    printf("sum = %ld\n", sum);
    pthread_exit((void *)1);
}

int main(void){

//    pthread_t tid;
    int err;
    void *tret;

    err = makethread(thr_function, NULL);
    if (err != 0){
        err_exit(err, "can't create thread 1");
    }

    err = pthread_join(tid, &tret);
    if (err != 0){
        err_exit(err, "can't join thread1");
    }
    printf("thread 1 exit code %ld\n", (long)tret);
    exit(0);
}