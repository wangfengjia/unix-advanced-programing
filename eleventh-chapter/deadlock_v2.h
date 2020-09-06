//
// Created by 王勇椿 on 2020/9/6.
//

#ifndef UNIX_ADVANCED_PROGRAMING_DEADLOCK_V2_H
#define UNIX_ADVANCED_PROGRAMING_DEADLOCK_V2_H

//由于deadlock_v1版本的加锁规则太过于复杂，所以对其进行优化

#include <pthread.h>

#define NHASH 29
#define HASH(id) (((unsigned long)id) % NHASH)

struct deadlock_foo_v2{
    int f_id;

    //在第一个版本中，这个字段是由f_lock互斥量保护，所以要保证在每个线程对f_lock和hashlock两个互斥量的加锁顺序
    //在第二个版本中，这个字段由hashlock保护，这样就不需要处理保证f_lock和hashlock加锁顺序的问题
    int f_count;
    pthread_mutex_t f_lock;
    struct deadlock_foo_v2 *next;
};

struct deadlock_foo_v2 *foo_table_v2[NHASH];
pthread_mutex_t myhashlock;

struct deadlock_foo_v2 *alloc_v2(int);
void hold_v2(struct deadlock_foo_v2 *);
struct deadlock_foo_v2 *find_v2(int);
void rele_v2(struct deadlock_foo_v2 *);
#endif //UNIX_ADVANCED_PROGRAMING_DEADLOCK_V2_H
