//
// Created by 王勇椿 on 2020/9/6.
//

#include "deadlock_v2.h"
#include "../include/apue.h"

int idx = 1;
struct deadlock_foo_v2 *foo_v2;

void *thr1_fun(void *);
void *thr2_fun(void *);
void *thr3_fun(void *);

void *thr1_fun(void *args){

    hold_v2(foo_v2);
    int i;
    pthread_mutex_lock(&myhashlock);
    for (i = 0; i < 100000; i++){
        foo_v2->f_count++;
    }
    pthread_mutex_unlock(&myhashlock);
    rele_v2(foo_v2);
    pthread_exit((void *)1);
}

void *thr2_fun(void *args){

    hold_v2(foo_v2);
    int i;
    pthread_mutex_lock(&myhashlock);
    for (i = 0; i < 100000; i++){
        foo_v2->f_count++;
    }
    pthread_mutex_unlock(&myhashlock);
    rele_v2(foo_v2);
    pthread_exit((void *)2);
}

void *thr3_fun(void *args){

    hold_v2(foo_v2);
    int i;
    pthread_mutex_lock(&myhashlock);
    for (i = 0; i < 100000; i++){
        foo_v2->f_count++;
    }
    pthread_mutex_unlock(&myhashlock);
    rele_v2(foo_v2);
    return ((void *)3);
}

int main(void){

    pthread_t tid1,tid2,tid3;
    int err;
    void *tret;

    if (alloc_v2(1) == NULL){
        err_sys("alloc v2 error");
    }
    if (alloc_v2(2) == NULL){
        err_sys("alloc v2 error");
    }

    foo_v2 = foo_table_v2[idx];
    err = pthread_create(&tid1, NULL, thr1_fun, NULL);
    if (err != 0){
        err_exit(err, "can't create thread 1");
    }
    err = pthread_create(&tid2, NULL, thr2_fun, NULL);
    if (err != 0){
        err_exit(err, "can't create thread 2");
    }
    err = pthread_create(&tid3, NULL, thr3_fun, NULL);
    if (err != 0){
        err_exit(err, "can't create thread 3");
    }

    err = pthread_join(tid1, &tret);
    if (err != 0){
        err_exit(err, "can't join thread 1");
    }
    printf("thread 1 exit code %ld\n", (long)tret);
    err = pthread_join(tid2, &tret);
    if (err != 0){
        err_exit(err, "can't join thread 2");
    }
    printf("thread 2 exit code %ld\n", (long)tret);
    err = pthread_join(tid3, &tret);
    if (err != 0){
        err_exit(err, "can't join thread 3");
    }
    printf("thread 3 exit code %ld\n", (long)tret);

    printf("count value: %d\n", foo_v2->f_count);
    exit(0);
}


