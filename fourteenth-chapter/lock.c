//
// Created by 王勇椿 on 2020/9/18.
//
#include "lock.h"
#include "../include/apue.h"

int
lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len){

    struct flock lock;
    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return (fcntl(fd, cmd, &lock));
}

int
lock_test(int fd, int type, off_t offset, int whence, off_t len){

    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    //F_GETLK判断有flockptr所描述的锁是否会被另外一把锁所排斥。如果存在一把锁，它阻止创建由flockptr所描述的锁,
    //则用现有锁的信息重写flockptr指向的结构.如果不存在这种情况，则会将l_type设置为F_UNLOCK
    if (fcntl(fd, F_GETLK, &lock) < 0){
        err_sys("fcntl error");
    }

    //可以对这个区域加这把锁
    if (lock.l_type == F_UNLCK){
        return 0;
    }

    //想加的锁被这个区域已加的锁所排斥
    return (lock.l_pid);
}
















