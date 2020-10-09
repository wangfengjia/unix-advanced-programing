//
// Created by 王勇椿 on 2020/10/6.
//
//信号量。与一般的IPC(管道、FIFO、消息队列)不同，它是一个计数器，作用是为多个进程提供对共享数据对象的访问
#include <sys/sem.h>

int
main(void){

    struct sembuf sembuf;

    struct semid_ds semid;

}

