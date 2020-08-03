//
// Created by 王勇椿 on 2020/8/3.
//

#include "../include/apue.h"
#include <sys/wait.h>

void process_control(void);

int main(void){

    printf("hello world from process ID %ld\n", (long)getpid());
    process_control();
    exit(0);
}

void process_control(void){

    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL){

        if (buf[strlen(buf) - 1] == '\n'){
            buf[strlen(buf) - 1] = 0;
        }

        if ((pid = fork()) < 0){
            err_sys("fork error");
        } else if (pid == 0){ //子进程
            execlp(buf, buf, (char *)0);
            err_ret("could not execute: %s", buf);
            exit(127);
        }

        //父进程
        if ((pid = waitpid(pid, &status, 0)) < 0){
            err_sys("waitpid error");
        }

        printf("%% ");
    }
}