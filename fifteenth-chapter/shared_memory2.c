//
// Created by 王勇椿 on 2020/10/7.
//
#include "../include/apue.h"
#include <fcntl.h>
#include <sys/mman.h>

/**
 * 设备/dev/zero，读此设备时它是0字节的无限资源；写这个设备时，它也接收写向它的任何数据，但又忽略这些数据
 * 将这个设备作为IPC时，当对其进程存储映射时，它具有一些特殊性质
 * 1.创建一个未命名的存储区，其长度为mmap函数的第二个参数，将其向上取整为系统的最近页长
 * 2.存储都初始化为0
 * 3.如果多个进程的共同祖先进程对mmap指定了MAP_SHARED标志,则这些进程可共享此存储区
 *
 * 以这种方式使用/dev/zero的
 * 1.优点:在调用mmap创建映射区之前，无需存在一个实际文件，映射/dev/zero自动创建一个指定长度的映射区
 * 2.缺点:它只在两个相关的进程之间起作用
 */


#define NLOOPS 1000
#define SIZE sizeof(long) // size of shared memory area

static int update(long *);

static int update(long *ptr){
    return ((*ptr)++); //return value before increment
}

int
main(void){

    int fd, i, counter;
    pid_t pid;
    void *area;

    if ((fd = open("/dev/zero", O_RDWR)) < 0){
        err_sys("open error");
    }
    //mmap指定了MAP_SHARED标志，多个进程可以共享此存储区
    if ((area = mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED){
        err_sys("mmap error");
    }
    close(fd); // can close /dev/zero now that it's closed

    TELL_WAIT();

    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid > 0){
        for (i = 0; i < NLOOPS; i++){
            if ((counter = update((long *)area)) != i){
                err_quit("parent: excepted %d, got %d", i, counter);
            }
            TELL_CHILD(pid);
            WAIT_CHILD();
        }
    } else{
        for (i = 0; i < NLOOPS; i++){

            WAIT_PARENT();
            if ((counter = update((long *)area)) != i){
                err_quit("child: excepted %d, got %d", i, counter);
            }
            TELL_PARENT(getppid());
        }
    }
    exit(0);
}

