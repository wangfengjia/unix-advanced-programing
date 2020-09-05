//
// Created by 王勇椿 on 2020/9/5.
//

//互斥量的实例

#include "mutex.h"
#include "../include/apue.h"
#include <stdlib.h>


struct mutex_foo *foo_alloc(int id){

    struct mutex_foo *foo;

    if ((foo = malloc(sizeof(struct mutex_foo))) == NULL){
        err_sys("malloc error");
    }

    //对这个对象初始化时不需要加锁，因为在这个操作之前分配线程是唯一引用该对象的线程
    //即使多个线程调用这个函数，由于是每次都会进行动态分配，所以是不同的对象
    foo->f_count = 1;
    foo->f_id = id;
    //初始化互斥量,假如初始化失败，则释放已经分配的空间
    if (pthread_mutex_init(&foo->f_lock, NULL) != 0){
        free(foo);
        return NULL;
    }

    return foo;
}

void foo_hold(struct mutex_foo *foo){
    pthread_mutex_lock(&foo->f_lock);
    foo->f_count++;
    pthread_mutex_unlock(&foo->f_lock);
}

void foo_rele(struct mutex_foo *foo){

    pthread_mutex_lock(&foo->f_lock);
    if (--foo->f_count == 0){ //对象的引用计数为0，则释放对象
        //由于互斥量的内存空间是通过malloc分配的，所以在释放内存前需要调用一下pthread_mutex_destroy()函数
        pthread_mutex_unlock(&foo->f_lock);
        pthread_mutex_destroy(&foo->f_lock);
        free(foo);
    } else{
        pthread_mutex_unlock(&foo->f_lock);
    }
}

