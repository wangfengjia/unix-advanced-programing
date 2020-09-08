//
// Created by 王勇椿 on 2020/9/6.
//

#ifndef UNIX_ADVANCED_PROGRAMING_CONDITION_VARIABLE_H
#define UNIX_ADVANCED_PROGRAMING_CONDITION_VARIABLE_H
/**
 * 条件变量，线程同步的另一种机制。条件变量给多个线程提供了汇合的场所。当条件发生改变了，给等待的线程发信号
 * 通过调用pthread_cond_wait函数，会把调用线程放到等待条件的列表上，将传递的互斥量解锁，pthread_cond_wait函数返回时，互斥量再次被锁住
 * 当条件发生改变时，调用pthread_cond_signal(至少唤醒一个等待条件的线程)函数
 * 或者pthread_cond_broadcast(唤醒等待条件的所有线程)函数给线程发信息，等待条件的线程就会被唤醒
 */

#include <pthread.h>

#define MESSAGE_LENTH 64
struct message{

    struct message *m_next;
    char content[MESSAGE_LENTH];
};


void process_message(void);
void enqueue_message(struct message *);

#endif //UNIX_ADVANCED_PROGRAMING_CONDITION_VARIABLE_H
