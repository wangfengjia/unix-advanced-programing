//
// Created by 王勇椿 on 2020/8/17.
//

//当一个子进程的父进程先于子进程终止时，此时子进程的父进程会被设置为init进程(ID为1的进程)
#include <stddef.h>
#include "../include/apue.h"


int main(void){

    pid_t pid;
    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid == 0){
        while (getppid() != 1){

        }
        printf("parent process id: %d", getppid());
//        exit(0);
    } else{
        exit(0);
    }


}

