//
// Created by 王勇椿 on 2020/9/10.
//
//一个函数可被多个线程同时安全调用，则这个函数是线程安全的。一个函数可以被多个线程重入，它也是线程安全的

//例子:getenv函数的线程安全版
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <stddef.h>
#include "thread_safe.h"

extern char **environ;

pthread_mutex_t env_mutex;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;



static void thread_init(void){

    pthread_mutexattr_t mutexattr;

    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&env_mutex, &mutexattr);
    pthread_mutexattr_destroy(&mutexattr);
}

//使用pthread_once函数来确保不管多少线程同时来竞争调用getenv_r，每个进程只调用thread_init函数一次
int getenv_r(const char *name, char *buf, int buflen){

    int i, len, olen;
    pthread_once(&init_done, thread_init);
    len = strlen(name);
    pthread_mutex_lock(&env_mutex);
    for (i = 0; environ[i] != NULL; i++){
        if ((strncmp(name, environ[i], len) == 0) && environ[i][len] == '='){
            olen = strlen(&environ[i][len + 1]);
            if (olen >= buflen){
                pthread_mutex_unlock(&env_mutex);
                return (ENOSPC);
            }

            strcpy(buf, &environ[i][len + 1]);
            pthread_mutex_unlock(&env_mutex);
            return (0);
        }
    }
    pthread_mutex_unlock(&env_mutex);
    return (ENOENT);
}

