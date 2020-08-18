//
// Created by 王勇椿 on 2020/8/17.
//
//创建子进程

#include "../include/apue.h"

int globval = 6;
char buf[] = "a write to stdout\n";

int main(void){

    int val;
    pid_t pid;

    val = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1){
        err_sys("write error");
    }

    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid == 0){ //子进程
        globval++;
        val++;
    } else{ //父进程
        sleep(2);
    }

    printf("pid = %ld, glob = %d, val = %d\n", (long)getpid(), globval, val);
    exit(0);
}

