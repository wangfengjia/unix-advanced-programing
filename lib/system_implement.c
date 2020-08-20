//
// Created by 王勇椿 on 2020/8/20.
//
//system函数的一种实现，无信号处理
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stddef.h>
#include "../include/my_apue.h"

int mysystem(const char *cmdstring){

    pid_t pid;
    int status;

    if (cmdstring == NULL){
        return (1);
    }

    if ((pid = fork()) < 0){
        status = -1;
    } else if (pid == 0){
        if (execl("/bin/sh", "sh", "-c", cmdstring, (char *)0));
        _exit(127); //不使用exit函数是为了防止任一标准I/O缓冲(fork中由父进程复制到子进程)被子进程冲洗
    } else{

        while (waitpid(pid, &status, 0) < 0){
            if (errno != EINTR){
                status = -1;
                break;
            }
        }
    }

    return status;
}

