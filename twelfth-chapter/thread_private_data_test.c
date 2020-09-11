//
// Created by 王勇椿 on 2020/9/11.
//
#include <pthread.h>
#include "thread_private_data.h"
#include "../include/apue.h"

pthread_barrier_t b;
void *thread_fun(void *arg);

void *thread_fun(void *arg){

    char *home = thread_private_getenv("HOME");
    printf("home content: %s\n", home);
    print_address();

    pthread_barrier_wait(&b);
    return ((void *)0);
}

int main(void){

    int i;
    int err;
    pthread_t tid;

    pthread_barrier_init(&b, NULL, 3);
    for (i = 0; i < 2; i++){
        err = pthread_create(&tid, NULL, thread_fun, NULL);
        if (err != 0){
            err_exit(err, "can't create thread");
        }
    }
    pthread_barrier_wait(&b);

    exit(0);
}















