//
// Created by 王勇椿 on 2020/9/18.
//
//两个进程互相等待对方持有并且不释放的资源时，则这两个进程处于死锁状态
//例子:子进程:先对第0字节加写锁，然后对第1字节加写锁；父进程:先对第1字节加写锁，然后对第0字节加写锁
//检测到死锁时，内核必须选择一个进程接受出错信息
#include "../include/apue.h"
#include <fcntl.h>

static void lockabyte(const char *, int, off_t);

static void lockabyte(const char *name, int fd, off_t offset){

    if (writew_lock(fd, offset, SEEK_SET, 1) < 0){
        err_sys("%s: writew_lock error", name);
    }

    printf("%s: got the lock, byte %lld\n", name, (long long)offset);
}

int
main(void){

    int fd;
    pid_t pid;

    if ((fd = creat("tmplock", FILE_MODE)) < 0){
        err_sys("create error");
    }
    if (write(fd, "ab", 2) != 2){
        err_sys("write error");
    }

    TELL_WAIT();
    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid == 0){ //child process
        lockabyte("child", fd, 0);
        //每个进程等待另外一个进程获得它设置的第一把锁
        TELL_PARENT(getppid());
        WAIT_PARENT();
        lockabyte("child", fd, 1);
    } else{
        lockabyte("parent", fd, 1);
        TELL_CHILD(pid);
        WAIT_CHILD();
        lockabyte("parent", fd, 0);
    }

    exit(0);
}