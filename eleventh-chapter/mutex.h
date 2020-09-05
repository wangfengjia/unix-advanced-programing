//
// Created by 王勇椿 on 2020/9/5.
//互斥量
//

#ifndef UNIX_ADVANCED_PROGRAMING_MUTEX_H
#define UNIX_ADVANCED_PROGRAMING_MUTEX_H

#include <pthread.h>

struct mutex_foo{
    int f_count; //对象的引用计数
    pthread_mutex_t f_lock; //对象的互斥量
    int f_id;
};

struct mutex_foo *foo_alloc(int);
//线程在使用对象前调用，给这个对象的引用计数加1
void foo_hold(struct mutex_foo *);
//当线程使用对象完毕时调用，释放线程对这个对象的引用。当最后一个引用被释放时，对象所占的内存空间就被释放
void foo_rele(struct mutex_foo *);

#endif //UNIX_ADVANCED_PROGRAMING_MUTEX_H
