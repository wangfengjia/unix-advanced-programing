//
// Created by 王勇椿 on 2020/9/16.
//
//子进程初始只有父进程执行fork函数的线程的副本。子进程继承了父进程的虚拟地址空间，还从父进程继承了每个互斥量、读写锁和条件变量的状态
//如果父进程的线程占有锁，子进程将同样占有这些锁，可以通过调用pthread_atfork函数清除这些锁状态

#include <pthread.h>
#include "../include/apue.h"

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void prepare(void);
void parent(void);
void child(void);
void *thr_function(void *args);

void prepare(void){

    int err;
    printf("preparing locks...\n");
    if ((err = pthread_mutex_lock(&lock1)) != 0){
        err_exit(err, "can't lock lock1 in prepare handler");
    }
    if ((err = pthread_mutex_lock(&lock2)) != 0){
        err_exit(err, "can't lock lock2 in prepare handler");
    }
}

void parent(void){

    int err;

    printf("parent unlocking locks....\n");
    if ((err = pthread_mutex_unlock(&lock1)) != 0){
        err_exit(err, "can't unlock lock1 in parent handler");
    }
    if ((err = pthread_mutex_unlock(&lock2)) != 0){
        err_exit(err, "can't unlock lock2 in parent handler");
    }
}

void child(void){

    int err;

    printf("child unlocking locks...\n");
    if ((err = pthread_mutex_unlock(&lock1)) != 0){
        err_exit(err, "can't unlock lock1 in child handler");
    }
    if ((err = pthread_mutex_unlock(&lock2)) != 0){
        err_exit(err, "can't unlock lock2 in child handler");
    }
}

void *thr_function(void *arg){

    printf("thread started....\n");
    pause();
    return ((void *)0);
}

int main(void){

    int err;
    pid_t pid;
    pthread_t tid;

    if ((err = pthread_atfork(prepare, parent, child)) != 0){
        err_exit(err, "can't install fork handlers");
    }

    if ((err = pthread_create(&tid, NULL, thr_function, NULL)) != 0){
        err_exit(err, "can't create thread");
    }

    sleep(2);
    printf("parent about fork...\n");

    if ((pid = fork()) < 0){
        err_quit("fork failed");
    } else if (pid == 0){ //child process
        printf("child returned from fork\n");
    } else{
        printf("parent returned from fork\n");
    }
    exit(0);
}

