//
// Created by 王勇椿 on 2020/9/6.
//

#ifndef UNIX_ADVANCED_PROGRAMING_DEADLOCK_V1_H
#define UNIX_ADVANCED_PROGRAMING_DEADLOCK_V1_H
//出现死锁的情况:当需要多个互斥量时，每个线程对互斥量的加锁顺序不一致，这样就可能出现死锁
//解决方案:需要多个互斥量的时候，总是用相同的顺序对他们加锁

#include <pthread.h>
#define NHASH 29
#define HASH(id) (((unsigned long)id) % NHASH)

pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct deadlock_foo{
    int f_count;
    pthread_mutex_t f_clock;
    int f_id;
    struct deadlock_foo *next;
};

//数组元素是指向deealock_foo结构的指针
struct deadlock_foo *foo_table[NHASH];
struct deadlock_foo *alloc_v1(int);
void hold_v1(struct deadlock_foo *foo);
struct deadlock_foo *find_v1(int);
void rele_v1(struct deadlock_foo *);
#endif //UNIX_ADVANCED_PROGRAMING_DEADLOCK_V1_H
