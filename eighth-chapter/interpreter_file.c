//
// Created by 王勇椿 on 2020/8/19.
//
#include "../include/apue.h"
#include <sys/wait.h>

int main(void){

    pid_t pid;

    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid == 0){
        if (execl("/Users/wangyongchun/www/study/c/unix-advanced-programing/eighth-chapter/testinterpre",
                  "testinterpre", "myarg1", "MY ARG2", (char *)0) < 0){
            err_sys("execl error");
        }
    }

    if (waitpid(pid, NULL, 0) < 0){
        err_sys("waitpid error");
    }

    exit(0);
}

