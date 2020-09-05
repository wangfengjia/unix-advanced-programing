//
// Created by 王勇椿 on 2020/9/5.
//
/**
 * 线程清理处理程序，以下三个动作会触发执行线程清理处理程序
 * 1.调用pthread_exit函数
 * 2.响应取消请求
 * 3.用非零execute参数调用pthread_clean_up时
 */

#include <pthread.h>
#include "../include/apue.h"

void cleanup(void *args);
void *thr1_function(void *args);
void *thr2_function(void *args);


void cleanup(void *args){
    printf("cleanup: %s\n", (char *)args);
}

void *thr1_function(void *args){

    printf("thread 1 start\n");
    pthread_cleanup_push(cleanup, "thread 1 first handler");
    pthread_cleanup_push(cleanup, "thread 1 second handler");
    printf("thread 1 push complete\n");
    if (args){
        return (void *)1;
    }
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return (void *)1;
}

void *thr2_function(void *args){
    printf("thread 2 start\n");
    pthread_cleanup_push(cleanup, "thread 2 first handler");
    pthread_cleanup_push(cleanup, "thread 2 second handler");
    if (args){
        pthread_exit((void *)2);
    }
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit((void *)2);
}

int main(void){

    int err;
    pthread_t  tid1, tid2;
    void *tret;

    err = pthread_create(&tid1, NULL, thr1_function, (void *)1);
    if (err != 0){
        err_exit(err, "can't create thread 1");
    }
    err = pthread_create(&tid2, NULL, thr2_function, (void *)1);
    if (err != 0){
        err_exit(err, "can't create thread 2");
    }
    err = pthread_join(tid1, &tret);
    if (err != 0){
        err_exit(err, "can't join with thread 1");
    }
    err = pthread_join(tid2, &tret);
    if (err != 0){
        err_exit(err, "can't join with thread 2");
    }
    printf("thread 2 exit code %ld\n", (long)tret);
    exit(0);
}




