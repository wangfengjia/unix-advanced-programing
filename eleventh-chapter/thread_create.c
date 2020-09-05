//
// Created by 王勇椿 on 2020/9/4.
//
//pthread_create()函数创建线程

#include <pthread.h>
#include "../include/apue.h"

void printids(const char *);
void *thr_fn(void *);

pthread_t ntid;

int main(void){

    int err;
    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (err != 0){
        err_exit(err, "can't create thread");
    }
    printids("main thread:");
    sleep(1);
    exit(0);
}

void printids(const char *str){

    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n", str, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}

void *thr_fn(void *arg){
    printids("new thread: ");
    return (void *)0;
}

