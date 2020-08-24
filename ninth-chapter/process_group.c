//
// Created by 王勇椿 on 2020/8/24.
//
//每个进程有一个进程ID，而且还会属于一个进程组

#include <unistd.h>
#include "../include/apue.h"

int main(void){

    pid_t pid;

    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid == 0){
        printf("child process id: %d, group id: %d\n", getpid(), getpgrp());
    } else{
        printf("parent process id: %d, group id: %d\n", getpid(), getpgrp());
    }
}
