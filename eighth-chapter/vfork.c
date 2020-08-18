//
// Created by 王勇椿 on 2020/8/17.
//
#include "../include/apue.h"

int globval = 6;

int main(void){

    int val;
    pid_t pid;

    val = 88;
    printf("before vfork\n");
    if ((pid = vfork()) < 0){
        err_sys("vfork error");
    } else if (pid == 0){
        globval++;
        val++;
        _exit(0); //子进程调用这个函数，父进程恢复运行
    }


    //父进程
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globval, val);
    exit(0);
}

