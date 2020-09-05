//
// Created by 王勇椿 on 2020/9/5.
//
#include "mutex.h"
#include "../include/apue.h"

int d = 0;
pthread_mutex_t lock;
struct mutex_foo *foo;

void *mutex_thr1_function(void *args);
void *mutex_thr2_function(void *args);
void *mutex_thr3_function(void *args);

void *mutex_thr1_function(void *args){

    foo_hold(foo);
    int i = 0;
    for (; i < 1000000; i++){
//        pthread_mutex_lock(&foo->f_lock);
        ++foo->f_id;
//        ++d;
//        pthread_mutex_unlock(&lock);
//        pthread_mutex_unlock(&foo->f_lock);
    }
    foo_rele(foo);
    pthread_exit((void *)1);
}

void *mutex_thr2_function(void *args){

//    foo_hold(foo);
    int i = 0;
    for (; i < 1000000; i++){
//        pthread_mutex_lock(&foo->f_lock);
        ++foo->f_id;
//        ++d;
//        pthread_mutex_unlock(&lock);
//        pthread_mutex_unlock(&foo->f_lock);
    }
//    foo_rele(foo);
    pthread_exit((void *)2);
}

void *mutex_thr3_function(void *args){

//    foo_hold(foo);
    int i = 0;
    for (; i < 1000000; i++){
//        pthread_mutex_lock(&foo->f_lock);
        ++foo->f_id;
//        ++d;
//        pthread_mutex_unlock(&lock);
//        pthread_mutex_unlock(&foo->f_lock);
    }
//    foo_rele(foo);
    return ((void *)3);
}

int main(void){

    pthread_t tid1, tid2, tid3;
    void *tret;
    int err;

//    if (pthread_mutex_init(&lock, NULL) != 0){
//        err_sys("init mutex error");
//    }
    if ((foo = foo_alloc(0)) == NULL){
        err_sys("alloc foo failed");
    }

    err = pthread_create(&tid1, NULL, mutex_thr1_function, NULL);
    if (err != 0){
        err_exit(err, "can't create thread 1");
    }
    err = pthread_create(&tid2, NULL, mutex_thr2_function, NULL);
    if (err != 0){
        err_exit(err, "can't create thread 2");
    }

    err = pthread_create(&tid3, NULL, mutex_thr3_function, NULL);
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

    printf("id: %d\n", foo->f_id);
    exit(0);
}



