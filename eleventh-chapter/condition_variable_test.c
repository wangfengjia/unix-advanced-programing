//
// Created by 王勇椿 on 2020/9/6.
//
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "condition_variable.h"
#include "../include/apue.h"


void *condition_thr1_function(void *args);
void *condition_thr2_function(void *args);
void *condition_thr3_function(void *args);

void *condition_thr1_function(void *args){

    while (true){
        process_message();
    }
}

void *condition_thr2_function(void *args){

    while (true){
        process_message();
    }
}

void *condition_thr3_function(void *args){

    struct message *message;

    int i = 0;
    for (; i < 15; i++){
        if ((message = malloc(sizeof(struct message))) == NULL){
            err_sys("thread 3 malloc error");
        }
        sprintf(message->content, "message number: %d", i);
        enqueue_message(message);
    }

    pthread_exit((void *)3);
}

int main(void){

    pthread_t tid1, tid2, tid3;
    int err;

    err = pthread_create(&tid1, NULL, condition_thr1_function, NULL);
    if (err != 0){
        err_exit(err, "can't create thread 1");
    }
    err = pthread_create(&tid2, NULL, condition_thr2_function, NULL);
    if (err != 0){
        err_exit(err, "can't create thread 2");
    }
    err = pthread_create(&tid3, NULL, condition_thr3_function, NULL);
    if (err != 0){
        err_exit(err, "can't create thread 3");
    }

    err = pthread_join(tid1, NULL);
    if (err != 0){
        err_exit(err, "can't join with thread 1");
    }
    err = pthread_join(tid2, NULL);
    if (err != 0){
        err_exit(err, "can't join with thread 2");
    }
    err = pthread_join(tid3, NULL);
    if (err != 0){
        err_exit(err, "can't join with thread 3");
    }

    exit(0);
}
