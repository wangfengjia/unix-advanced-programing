//
// Created by 王勇椿 on 2020/8/18.
//
//父进程获取子进程的终止状态，当子进程终止时，内核会向父进程发送一个SIGCHILD信号

#include <sys/wait.h>
#include "pr_exit.h"
#include "../include/apue.h"

void tetst(void);
int main(void){


    pid_t pid;
    int status;

    if ((pid = fork()) < 0){
        err_sys("first fork error");
    } else if (pid == 0){
        exit(7);
    }

    if (wait(&status) != pid){
        err_sys("first wait error");
    }
    pr_exit(status);

    if ((pid = fork()) < 0){
        err_sys("second fork error");
    } else if (pid == 0){
        abort();
    }

    if (wait(&status) != pid){
        err_sys("second wait error");
    }
    pr_exit(status);

    if ((pid = fork()) < 0){
        err_sys("third fork error");
    } else if (pid == 0){
        status /= 0;
    }

    if (wait(&status) != pid){
        err_sys("third wait error");
    }
    pr_exit(status);

    exit(0);

}

