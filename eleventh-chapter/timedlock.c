//
// Created by 王勇椿 on 2020/9/6.
//
//当一个线程试图获取已经加锁的互斥量时，可以通过pthread_mutex_timedlock函数设置线程阻塞时间(线程等待锁的超时时间)

#include "../include/apue.h"
#include <pthread.h>
#include <time.h>

int main(void){

    int err;
    struct timespec out;
    struct tm *tmp;
    char buf[64];
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&lock);
    printf("mutex is locked\n");
    clock_gettime(CLOCK_REALTIME, &out);
    tmp = localtime(&out.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("current time is %s\n", buf);
    out.tv_sec += 10;
    //在实际中，线程不要试图对同一个互斥量加锁多次，这样互斥量自身就会陷入死锁
#ifdef LINUX
    pthread_mutex_timedlock(&lock, &out);
#else
    exit(0);
#endif
    clock_gettime(CLOCK_REALTIME, &out);
    tmp = localtime(&out.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("the time is now %s\n", buf);
    if (err == 0){
        printf("mutex locked again\n");
    } else{
        printf("can't lock mutex again:%s\n", strerror(err));
    }

    exit(0);
}

