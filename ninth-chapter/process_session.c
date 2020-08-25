//
// Created by 王勇椿 on 2020/8/24.
//
//进程会话:进程组的集合，会话ID会是会话首进程的进程ID

#include <unistd.h>
#include "../include/apue.h"

int main(void){

    pid_t pid;

    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid == 0){

//        while (getppid() != 1){
//            sleep(1);
//        }
        pid_t sessionid;
        pid_t groupid;
        if ((sessionid = setsid()) < 0){
            printf("setsid() error");
        }

        if ((groupid = getsid(getpid())) < 0){
            printf("getsid() error");
        }

        printf("processid: %d, groupid: %d, return group id:%d", getpid(), groupid, sessionid);
    }

    exit(0);

//    exit(0);

}
