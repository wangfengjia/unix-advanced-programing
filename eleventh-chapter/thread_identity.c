//
// Created by 王勇椿 on 2020/9/4.
//

//利用pthread_self()函数来获取自身线程ID

#include <pthread.h>
#include "../include/apue.h"

int main(void){

    pthread_t thread_id = pthread_self();
    printf("thread id: %ld\n", thread_id->__sig);
}
