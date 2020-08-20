//
// Created by 王勇椿 on 2020/8/18.
//

#include "../include/apue.h"
#include "pr_exit.h"
#include <sys/wait.h>


int main(void){

    pid_t pid;
    siginfo_t siginfo;
    int status;

    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid == 0){
        printf("parent process id: %ld\n", (long)getppid());
        exit(7);
    }

    if (waitid(P_PID, pid, &siginfo, WEXITED) < 0){
        err_sys("waitid error");
    }

    pr_exit(siginfo.si_code);
}

