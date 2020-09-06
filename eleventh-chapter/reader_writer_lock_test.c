//
// Created by 王勇椿 on 2020/9/6.
//
#include <stdbool.h>
#include "reader_writer_lock.h"
#include "../include/apue.h"

struct queue *queue;

void *thr1_function(void *args);
void *thr2_function(void *args);
void *thr3_function(void *args);

void *handler(pthread_t);


void *thr1_function(void *args){

    struct job *job;
    pthread_t tid = pthread_self();
    while (true){
        job = job_find(queue, tid);
        if (job != NULL){
            job_remove(queue, job);
            job->jobHandler(job->j_tid);
        }
    }

}

void *thr2_function(void *args){

    struct job *job;
    pthread_t tid = pthread_self();
    while (true){
        job = job_find(queue, tid);
        if (job != NULL){
            job_remove(queue, job);
            job->jobHandler(job->j_tid);
        }
    }
}

void *thr3_function(void *args){

    struct job *job;
    pthread_t tid = pthread_self();
    while (true){
        job = job_find(queue, tid);
        if (job != NULL){
            job_remove(queue, job);
            job->jobHandler(job->j_tid);
        }
    }
}

void *handler(pthread_t tid){

    printf("param thread id %lu, actual tread id %lu\n", (unsigned long)tid, (unsigned long)pthread_self());
    return ((void *)0);
}

int main(void){

    pthread_t tid1, tid2, tid3;
    pthread_t tid_arr[3];

    struct job *job;
    int err;

    err = pthread_create(&tid1, NULL, thr1_function, NULL);
    if (err != 0){
        err_exit(err, "can't create thread 1");
    }
    err = pthread_create(&tid2, NULL, thr2_function, NULL);
    if (err != 0){
        err_exit(err, "can't create thread 2");
    }
    err = pthread_create(&tid3, NULL, thr3_function, NULL);
    if (err != 0){
        err_exit(err, "can't create thread 3");
    }

    tid_arr[0] = tid1;
    tid_arr[1] = tid2;
    tid_arr[2] = tid3;

    if ((queue = malloc(sizeof(struct queue))) == NULL){
        err_sys("malloc error");
    }
    if (queue_init(queue) != 0){
        err_sys("queue init error");
    }

    int jobnum = 20;
    int point = 0;
    for (; point < jobnum; point++){
        if ((job = malloc(sizeof(struct job))) == NULL){
            err_sys("malloc struct job error");
        }
        job->j_tid = tid_arr[point % 2];
        job->jobHandler = handler;
        job_append(queue, job);
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    exit(0);
}



