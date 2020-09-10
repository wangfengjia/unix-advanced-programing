//
// Created by 王勇椿 on 2020/9/8.
//
//线程栈的大小

#include "../include/apue.h"
#include <pthread.h>

int main(void){

    pthread_attr_t attr;
    int err;
    size_t stack_size;

    err = pthread_attr_init(&attr);
    if (err != 0){
        err_exit(err, "pthread attr init error");
    }

    err = pthread_attr_getstacksize(&attr, &stack_size);
    if (err != 0){
        err_exit(err, "get stack size error");
    }

    printf("default stack size = %ld", stack_size);
    pthread_attr_destroy(&attr);
    exit(0);
}

