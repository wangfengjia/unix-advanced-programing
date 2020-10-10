//
// Created by 王勇椿 on 2020/10/9.
//
//POSIX信号量
//例子:假设我们将要创建自己的锁，这种锁能被一个线程加锁而被另外一个线程解锁。基于信号量来实现这个锁(互斥原语)
#include "posix_sem.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stddef.h>

struct slock *s_alloc(){

    struct slock *sp;
    static int cnt;

    if ((sp = malloc(sizeof(struct slock))) == NULL){
        return (NULL);
    }

    do {
        snprintf(sp->name, sizeof(sp->name), "/%ld.%d", (long)getpid(), cnt++);
        sp->sem = sem_open(sp->name, O_CREAT|O_EXCL, S_IRWXU, 1);
    }while ((sp->sem == SEM_FAILED) && (errno == EEXIST));
    if (sp->sem == SEM_FAILED){
        free(sp);
        return (NULL);
    }

    sem_unlink(sp->name);
    return (sp);
}

void s_free(struct slock *sp){
    sem_close(sp->sem);
    free(sp);
}

int s_lock(struct slock *sp){
    return (sem_wait(sp->sem));
}

int s_trylock(struct slock *sp){
    return (sem_trywait(sp->sem));
}

int s_unlock(struct slock *sp){
    return sem_post(sp->sem);
}

