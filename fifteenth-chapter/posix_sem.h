//
// Created by 王勇椿 on 2020/10/9.
//

#ifndef UNIX_ADVANCED_PROGRAMING_POSIX_SEM_H
#define UNIX_ADVANCED_PROGRAMING_POSIX_SEM_H
#include <semaphore.h>
#include <limits.h>

struct slock{
    sem_t *sem;
    char name[_POSIX_NAME_MAX];
};

struct slock *s_alloc();
void s_free(struct slock *sp);
int s_lock(struct slock *sp);
int s_trylock(struct slock *sp);
int s_unlock(struct slock *sp);

#endif //UNIX_ADVANCED_PROGRAMING_POSIX_SEM_H
