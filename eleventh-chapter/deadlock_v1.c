//
// Created by 王勇椿 on 2020/9/6.
//
//需要多个互斥量时，每个线程总是以相同的顺序对互斥量加锁，避免死锁

#include <stdlib.h>
#include "deadlock_v1.h"
#include "../include/apue.h"

struct deadlock_foo *alloc_v1(int id){

    struct deadlock_foo *foo;
    int idx;

    if ((foo = malloc(sizeof(struct deadlock_foo))) == NULL){
        err_sys("malloc error");
    }
    foo->f_id = id;
    foo->f_count = 1;
    if (pthread_mutex_init(&foo->f_clock, NULL) != 0){
        free(foo);
        return NULL;
    }
    idx = HASH(id);
    //将新的结构放到hash表前，需要对hashlock互斥量加锁
    pthread_mutex_lock(&hashlock);
    foo->next = foo_table[idx];
    foo_table[idx] = foo;
    //先锁住新结构中的互斥量。因为新的结构现在是放到全局散列表中了，其他线程可以找到它，所以在完成初始化之前，需要阻塞其他线程访问新结构
    pthread_mutex_lock(&foo->f_clock);
    foo->f_id += 2;
    pthread_mutex_unlock(&hashlock);
    pthread_mutex_unlock(&foo->f_clock);

    return foo;
}

void hold_v1(struct deadlock_foo *foo){
    pthread_mutex_lock(&foo->f_clock);
    ++foo->f_count;
    pthread_mutex_unlock(&foo->f_clock);
}

struct deadlock_foo *find_v1(int id){

    struct deadlock_foo *foo;

    //查找前先对保护哈希表的互斥量加锁
    pthread_mutex_lock(&foo->f_clock);
    for (foo = foo_table[HASH(id)]; foo != NULL; foo = foo->next){
        if (foo->f_id == id){
            //对找到的结构对象的引用计数加1
            hold_v1(foo);
            break;
        }
    }
    pthread_mutex_unlock(&foo->f_clock);
    return foo;
}

void rele_v1(struct deadlock_foo *foo){


    struct deadlock_foo *tfp;
    int idx;

    //为了读取指针foo的结构的字段，对foo结构对应的互斥量加锁，判断完成后再次释放锁的目的是为了保证加锁的顺序一致
    // (和find函数和alloc函数里面的加锁顺序一致，先对哈希表对应的互斥量hashlock加锁，然后对结构的互斥量f_lock进行加锁)，不出现死锁
    //在第一次获取结构foo的f_lock到再次获取结构foo的f_lock这段时间内foo结构的成员值发生了改变，所以需要重新检查条件
    pthread_mutex_lock(&foo->f_clock);
    if (foo->f_count == 1){
        pthread_mutex_unlock(&foo->f_clock);
        pthread_mutex_lock(&hashlock);
        pthread_mutex_lock(&foo->f_clock);
        //need recheck condition
        if (foo->f_count != 1){
            foo->f_count--;
            pthread_mutex_unlock(&hashlock);
            pthread_mutex_unlock(&foo->f_clock);
            return;
        }

        //remove from list
        idx = HASH(foo->f_id);
        tfp = foo_table[idx];
        if (tfp == foo){
            foo_table[idx] = foo->next;
        } else{
            while (tfp->next != foo){
                tfp = tfp->next;
            }
            tfp->next = foo->next;
        }
        pthread_mutex_unlock(&hashlock);
        pthread_mutex_unlock(&foo->f_clock);
        pthread_mutex_destroy(&foo->f_clock);
        free(foo);
    } else{
        foo->f_count--;
        pthread_mutex_unlock(&foo->f_clock);
    }

}

