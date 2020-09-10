//
// Created by 王勇椿 on 2020/9/8.
//
//线程的guardsize属性:在线程栈末尾以防栈溢出的扩展内存的大小，这个属性的默认值一般是系统页大小

#include "../include/apue.h"
#include <pthread.h>

int main(void){

    pthread_attr_t attr;
    size_t guardsize;
    int err;

    err = pthread_attr_init(&attr);
    if (err != 0){
        err_exit(err, "pthread attr init error");
    }

    err = pthread_attr_getguardsize(&attr, &guardsize);
    if (err != 0){
        err_exit(err, "pthread attr get guardsize error");
    }

    printf("guardsize = %ld\n", guardsize);
    pthread_attr_destroy(&attr);
    exit(0);
}

