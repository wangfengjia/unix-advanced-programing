//
// Created by 王勇椿 on 2020/9/9.
//
//互斥量对象的属性:进程共享属性、健壮属性、类型属性(4种类型)
//有必要使用递归互斥量的一种情形:有一个超时函数，它允许安排另一个函数在未来的时间运行。假设线程并不是一个昂贵的资源，就可以为每个挂起的超时函数创建一个线程
//线程在时间未到时将一直等待，时间到了以后再调用请求的函数

#include "../include/apue.h"
#include "detach_state.h"
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

extern makethread(void *(*)(void *), void *);

struct to_info{

    void (*to_fn)(void *); //function
    void *to_arg; //argument
    struct timespec to_wait; //time to wait
};
pthread_mutexattr_t mutexattr;
pthread_mutex_t mutex;

#define SECTONSEC 1000000000 //seconds to nanoseconds,秒换算为微秒
#if !defined(CLOCK_REALTIME) || defined(BSD)
#define clock_nanosleep(ID, FL, REQ, REM) nanosleep((REQ), (REM))
#endif

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#define USECTONSEC 1000 //微妙到纳秒换算

void clock_gettime(int id, struct timespec *);
void clcok_gettime(int id, struct timespec *tsp){

    struct timeval tv;

    gettimeofday(&tv, NULL);
    tsp->tv_sec = tv.tv_sec;
    tsp->tv_nsec = tv.tv_usec * USECTONSEC;
}
#endif

void *timeout_helper(void *);
void timeout(const struct timespec *, void (*)(void *), void *);
void retry(void *);

void *timeout_helper(void *arg){

    struct to_info *tip;

    tip = (struct to_info *)arg;
    clock_nanosleep(CLOCK_REALTIME, 0, &tip->to_wait, NULL);
    (*tip->to_fn)(tip->to_arg);
    free(arg);
    return 0;
}

void timeout(const struct timespec *when, void (*func)(void *), void *arg){

    struct timespec now;
    struct to_info *tip;
    int err;

    clock_gettime(CLOCK_REALTIME, &now);
    if ((when->tv_sec > now.tv_sec) || (when->tv_sec == now.tv_sec && when->tv_nsec > now.tv_nsec)){
        tip = malloc(sizeof(struct to_info));
        if (tip != NULL){
            tip->to_fn = func;
            tip->to_arg = arg;
            tip->to_wait.tv_sec = when->tv_sec - now.tv_sec;
            if (when->tv_nsec >= now.tv_nsec){
                tip->to_wait.tv_nsec = when->tv_nsec - now.tv_nsec;
            } else{
                //换算
                tip->to_wait.tv_sec--;
                tip->to_wait.tv_nsec = SECTONSEC - now.tv_nsec + when->tv_sec;
            }

            err = makethread(timeout_helper, (void *)tip);
            if (err == 0){
                return;
            } else{
                free(tip);
            }
        }
    }

    /**
     * 有三种情况会执行到这里
     * 1.when <= now 时间到了
     * 2.malloc failed
     * 3.can't create a thread, so we just call the function now
     */
    (*func)(arg);
}


void retry(void *arg){

    pthread_mutex_lock(&mutex);
    //perform retry step
    pthread_mutex_unlock(&mutex);
}

int main(void){

    int err, condition, arg;
    struct timespec when;

    if ((err = pthread_mutexattr_init(&mutexattr)) != 0){
        err_exit(err, "pthread_mutexarr_init failed");
    }
    if ((err = pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE)) != 0){
        err_exit(err, "can't set recursive type");
    }
    if ((err = pthread_mutex_init(&mutex, &mutexattr)) != 0){
        err_exit(err, "can't create recursive mutex");
    }

    pthread_mutex_lock(&mutex);
    /**
     * check the condition under the protection of a lock
     * to make the check and to call to timeout atomic
     */
     if (condition){
         //calculate the absolute time when we want to retry
         clock_gettime(CLOCK_REALTIME, &when);
         when.tv_sec += 10;
         timeout(&when, retry, (void *)((unsigned long)arg));
     }
    pthread_mutex_unlock(&mutex);
}



