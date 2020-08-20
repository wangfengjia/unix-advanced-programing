//
// Created by 王勇椿 on 2020/8/18.
//

#include "../include/apue.h"
#include <sys/wait.h>

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};


int main(void){

    pid_t pid;
    if ((pid = fork()) < 0){
        err_sys("first fork error");
    } else if (pid == 0){
        if (execle("/Users/wangyongchun/www/study/c/unix-advanced-programing/eighth-chapter/echoall",
                   "echoall", "myarg1", "MY ARG2", (char *)0, env_init) < 0){
            err_sys("execle error");
        }
    }

    if (waitpid(pid, NULL, 0) < 0){
        err_sys("waitpid error");
    }

    if ((pid = fork()) < 0){
        err_sys("second fork error");
    } else if (pid == 0){
        putenv("PATH=/Users/wangyongchun/www/study/c/unix-advanced-programing/eighth-chapter");
        if (execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0){
            err_sys("execlp error");
        }
    }

    exit(0);
}