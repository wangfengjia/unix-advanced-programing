//
// Created by 王勇椿 on 2020/8/18.
//
//wait函数是只要有一个子进程终止就返回，可以使用waitpid来等待指定子进程终止

#include <sys/wait.h>
#include "../include/apue.h"
#include "pr_exit.h"

int main(void){

    pid_t pid1, pid2;
    int status;

    if ((pid1 = fork()) < 0){
        err_sys("first fork error");
    } else if (pid1 == 0){
        printf("pid1: %d\n", getpid());
        exit(7);
    }

    if ((pid2 = fork()) < 0){
        err_sys("second fork error");
    } else if (pid2 == 0){
        printf("pid2: %d\n", getpid());
        abort();
    }


    if (waitpid(pid2, &status, WUNTRACED) == pid2){
        printf("waitpid process id: %d\n", pid2);
    }
    pr_exit(status);
}
