//
// Created by 王勇椿 on 2020/9/11.
//
//线程私有数据(线程特定数据)

#include <limits.h>
#include <stddef.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include "thread_private_data.h"
#include "../include/apue.h"

#define MAXSTRINGSZ 4096

static pthread_key_t private_key;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char **environ;

static void my_thread_init(void);

static void my_thread_init(void){

    pthread_key_create(&private_key, free);
}

char *thread_private_getenv(const char *name){

    int i, len;
    char *env_buf;

    //使用pthread_once函数的目的是确保一个进程只执行一次my_thread_init函数，这样就可以避免键不会由于在初始化阶段的竞争而发生变动
    pthread_once(&init_done, my_thread_init);
    pthread_mutex_lock(&env_mutex);
    //当返回空指针时，需要先分配内存缓冲区(线程私有数据的内存),然后键与此内存缓冲区关联
    env_buf = pthread_getspecific(private_key);
    if (env_buf == NULL){
        env_buf = malloc(MAXSTRINGSZ);
        if (env_buf == NULL){
            pthread_mutex_unlock(&env_mutex);
            return NULL;
        }

        pthread_setspecific(private_key, env_buf);
    }

    len = strlen(name);
    for (i = 0; environ[i] != NULL; i++){
        if ((strncmp(name, environ[i], len) == 0) && (environ[i][len]) == '='){
            strncpy(env_buf, &environ[i][len + 1], MAXSTRINGSZ - 1);
            pthread_mutex_unlock(&env_mutex);
            return env_buf;
        }
    }
    pthread_mutex_unlock(&env_mutex);
    return NULL;
}

void print_address(void){

    char *env_buf = pthread_getspecific(private_key);
    printf("thread private data address: 0x%p\n", env_buf);
}


























