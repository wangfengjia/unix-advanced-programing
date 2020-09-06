//
// Created by 王勇椿 on 2020/9/6.
//

#ifndef UNIX_ADVANCED_PROGRAMING_READER_WRITER_LOCK_H
#define UNIX_ADVANCED_PROGRAMING_READER_WRITER_LOCK_H
//读写锁，同一个时间，只有一个线层可以获取到写模式的读写锁，而可以有多个线程可以获取到读模式的读写锁
//所以读写锁可以用于读多写少的数据结构
//例子:由主线程给其他线程分配作业，作业在各个线程单独执行

#include <pthread.h>

typedef void *job_handler(pthread_t);
struct job{
    struct job *j_prev;
    struct job *j_next;
    pthread_t j_tid;
    job_handler *jobHandler;
//    void *(*handler)(void);
};

struct queue{
    struct job *q_head;
    struct job *q_tail;
    pthread_rwlock_t rwlock;
};

int queue_init(struct queue *);
void job_insert(struct queue *, struct job *);
void job_append(struct queue *, struct job *);
void job_remove(struct queue *, struct job *);
struct job *job_find(struct queue *, pthread_t);

#endif //UNIX_ADVANCED_PROGRAMING_READER_WRITER_LOCK_H
