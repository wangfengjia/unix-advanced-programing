//
// Created by 王勇椿 on 2020/9/21.
//

/**
 * 强制性锁:对一个文件打开设置组ID位，关闭组执行位会开启这个文件的强制锁机制
 * 1.强制性锁会让内内核检查每一个调用open/write/read函数的进程是否违背正在访问的文件上的某一把锁
 */
 //例子用来确认一个系统是否支持强制性锁机制
#include "../include/apue.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

int
main(int argc, char *argv[]){

    int fd;
    pid_t pid;
    char buf[5];
    struct stat statbuf;

    if (argc != 2){
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0){
        err_sys("open error");
    }
    if (write(fd, "abcdef", 6) != 6){
        err_sys("write error");
    }

    //打开文件的设置组ID位和关闭组执行位
    if (fstat(fd, &statbuf) < 0){
        err_sys("fstat error");
    }
    if (fchmod(fd, (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0){
        err_sys("fchmod error");
    }

    TELL_WAIT();
    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid > 0){
        //父进程在文件上加写锁
        if (writew_lock(fd, 0, SEEK_SET, 0) < 0){
            err_sys("write_lock error");
        }

        TELL_CHILD(pid);
        if (waitpid(pid, NULL, 0) < 0){
            err_sys("waitpid error");
        }
    } else{ //子进程

        WAIT_PARENT();

        //将文件设置为非阻塞
        set_fl(fd, O_NONBLOCK);

        errno = 0;
        //尝试给已经加写锁的文件区域加读锁返回什么错误
        if (read_lock(fd, 0, SEEK_SET, 0) != -1){
            err_sys("child: read_lock succeeded");
        }
        printf("read_lock of already-locked region returned %d\n", errno);
      
        //尝试读加写锁的文件
        if (lseek(fd, 0, SEEK_SET) == -1){
            err_sys("lseek error");
        }
        if (read(fd, buf, 2) < 0){
            err_ret("read failed(mandatory locking works)");
        } else{
            printf("read ok (no mandatory locking), buf = %2.2s\n", buf);
        }
    }

    exit(0);
}





























