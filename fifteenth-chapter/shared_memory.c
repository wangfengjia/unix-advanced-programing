//
// Created by 王勇椿 on 2020/10/7.
//
//共享存储(共享内存)
//例子:打印一些特定系统存放各种类型的数据的位置信息
#include "../include/apue.h"
#include <sys/shm.h>

#define ARRAY_SIZE 40000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
#define SHM_MODE 0600 //user read/write

//uninitialized data = bss
char array[ARRAY_SIZE];

int
main(void){

    int shmid;
    char *ptr, *shmptr;

    printf("array[] from %p to %p\n", (void *)&array[0], (void *)&array[ARRAY_SIZE]);
    printf("stack around %p\n", (void *)&shmid);

    if ((ptr = malloc(MALLOC_SIZE)) == NULL){
        err_sys("malloc error");
    }
    printf("malloced from %p to %p\n", (void *)ptr, (void *)ptr+MALLOC_SIZE);

    if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0){
        err_sys("shmget error");
    }
    if ((shmptr = shmat(shmid, 0, 0)) == (void *) - 1){
        err_sys("shmat error");
    }
    printf("shared memory attached from %p to %p\n", (void *)shmptr, (void *)shmptr + SHM_SIZE);

    if (shmctl(shmid, IPC_RMID, 0) < 0){
        err_sys("shmctl error");
    }

    exit(0);
}

