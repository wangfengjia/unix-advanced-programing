//
// Created by 王勇椿 on 2020/9/6.
//

#include "reader_writer_lock.h"
#include "../include/apue.h"

int queue_init(struct queue *qp){

    int err;
    qp->q_head = NULL;
    qp->q_tail = NULL;
    //init reader-writer-lock
    err = pthread_rwlock_init(&qp->rwlock, NULL);
    if (err != 0){
        return err;
    }

    //continue initialization
    return 0;
}

//insert a job to head of queue
void job_insert(struct queue *qp, struct job *jp){

    pthread_rwlock_wrlock(&qp->rwlock);
    jp->j_next = qp->q_head;
    jp->j_prev = NULL;
    if (qp->q_head != NULL){
        //这边不需要维护tail的原因是插入一个节点的时候，链表的头和尾都是这个节点，后续再往链表头插入节点时，链表尾节点保持不变
        qp->q_head->j_prev = jp;
    } else{
        qp->q_tail = jp;
    }
    qp->q_head = jp;
    pthread_rwlock_unlock(&qp->rwlock);
}

//insert a job to tail of queue
void job_append(struct queue *qp, struct job *jp){

    pthread_rwlock_wrlock(&qp->rwlock);
    jp->j_next = NULL;
    jp->j_prev = qp->q_tail;
    if (qp->q_head != NULL){
        qp->q_tail->j_next = jp;
    } else{
        qp->q_head = jp;
    }
    qp->q_tail = jp;
    pthread_rwlock_unlock(&qp->rwlock);
}

//remove a given job from queue
void job_remove(struct queue *qp, struct job *jp){

    pthread_rwlock_wrlock(&qp->rwlock);
    if (qp->q_head == jp){
        qp->q_head = jp->j_next;
        //判断jp是否也是队列的尾结点，也就是此时队列里面只有一个节点，并且这个节点就是要被删除的节点,此时要更新链表的尾结点
        if (qp->q_tail == jp){
            qp->q_tail = NULL;
        } else{
            jp->j_next->j_prev = jp->j_prev;
        }
    } else if (qp->q_tail == jp){ //会进入到这个分支就意味着需要被删除的节点不是链表的头结点，也就是现在链表的节点数量至少为2
        qp->q_tail = jp->j_prev;
        jp->j_next = jp->j_next;
    } else{
        jp->j_next->j_prev = jp->j_prev;
        jp->j_prev->j_next = jp->j_next;
    }
    pthread_rwlock_unlock(&qp->rwlock);
}

//find a job for ge
struct job *job_find(struct queue *qp, pthread_t tid){

    struct job *job;

    //读模式对读写锁加锁
    if (pthread_rwlock_rdlock(&qp->rwlock) != 0){
        return NULL;
    }

    for (job = qp->q_head; job != NULL; job = job->j_next){
        if (pthread_equal(tid, job->j_tid)){
            break;
        }
    }

    pthread_rwlock_unlock(&qp->rwlock);
    return job;
}
