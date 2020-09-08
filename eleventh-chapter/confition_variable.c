//
// Created by 王勇椿 on 2020/9/6.
//
#include <stdbool.h>
#include "condition_variable.h"
#include "../include/apue.h"

struct message *workq;

pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void process_message(void){

    struct message *message;

    while (true){

        pthread_mutex_lock(&qlock);
        while (workq == NULL){
            //将调用线程放到等待条件的线程列表，然后对互斥量解锁
            pthread_cond_wait(&qready, &qlock);
        }
        message = workq;
        workq = message->m_next;
        pthread_mutex_unlock(&qlock);
        printf("thread: %lu, message: %s\n", (unsigned long)pthread_self(), message->content);
    }
}

void enqueue_message(struct message *message){

    pthread_mutex_lock(&qlock);
    message->m_next = workq;
    workq = message;
    pthread_mutex_unlock(&qlock);
    pthread_cond_broadcast(&qready);
}
