//
// Created by 王勇椿 on 2020/8/18.
//

//一个进程fork一个子进程，但是它不要等待子进程终止，也不希望子进程处于僵死状态直到父进程终止，实现的方法是fork两次

#include "../include/apue.h"
#include <sys/wait.h>

int main(void){

    pid_t pid;

    if ((pid = fork()) < 0){
        err_sys("first time fork error");
    } else if (pid == 0){
        if ((pid = fork()) < 0){
            err_sys("second time fork error");
        } else if (pid > 0){ //第一个子进程
            exit(0);
        }

        //第二个子进程，调用sleep的目的是保证在打印父进程时，第一个子进程已经终止
        while (getppid() != 1){

        }
//        sleep(20);
        printf("second child, parent pid = %ld\n", (long)getppid());
        exit(0);
    }

    //wait for first child
    if (waitpid(pid, NULL, 0) != pid){
        err_sys("waitpid error");
    }
    exit(0);
}
