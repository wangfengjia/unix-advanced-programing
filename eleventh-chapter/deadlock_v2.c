//
// Created by 王勇椿 on 2020/9/6.
//
#include "../include/apue.h"
#include "deadlock_v2.h"
#include <stdlib.h>

pthread_mutex_t myhashlock = PTHREAD_MUTEX_INITIALIZER;

struct deadlock_foo_v2 *alloc_v2(int id){

    struct deadlock_foo_v2 *foo;
    int idx;

    if ((foo = malloc(sizeof(struct deadlock_foo_v2))) == NULL){
        err_sys("malloc error");
    }
    foo->f_id = id;
    foo->f_count = 1;
    if (pthread_mutex_init(&foo->f_lock, NULL) != 0){
        free(foo);
        return NULL;
    }
    idx = HASH(id);
    pthread_mutex_lock(&myhashlock);
    foo->next = foo_table_v2[idx];
    foo_table_v2[idx] = foo;
    pthread_mutex_lock(&foo->f_lock);
    pthread_mutex_unlock(&myhashlock);
    id += 3;
    pthread_mutex_unlock(&foo->f_lock);

    return foo;
}

void hold_v2(struct deadlock_foo_v2 *foo){

    //结构的f_count字段改为由hashlock互斥量保护
    pthread_mutex_lock(&myhashlock);
    foo->f_count++;
    pthread_mutex_unlock(&myhashlock);
}

struct deadlock_foo_v2 *find_v2(int id){

    struct deadlock_foo_v2 *foo;

    pthread_mutex_lock(&myhashlock);
    for (foo = foo_table_v2[HASH(id)]; foo != NULL; foo = foo->next){
        if (foo->f_id == id){
            foo->f_count++;
            break;
        }
    }
    pthread_mutex_unlock(&myhashlock);
    return foo;
}

void rele_v2(struct deadlock_foo_v2 *foo){

    struct deadlock_foo_v2 *tfp;
    int idx;

    pthread_mutex_lock(&myhashlock);
    if (--foo->f_count == 0){
        idx = HASH(foo->f_id);
        tfp = foo_table_v2[idx];
        if (tfp == foo){
            foo_table_v2[idx] = foo->next;
        } else{
            while (tfp->next != foo){
                tfp = tfp->next;
            }
            tfp->next = foo->next;
        }
        pthread_mutex_unlock(&myhashlock);
        pthread_mutex_destroy(&myhashlock);
        free(foo);
    } else{
        pthread_mutex_unlock(&myhashlock);
    }
}

