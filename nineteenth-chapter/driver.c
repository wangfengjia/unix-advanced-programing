//
// Created by 王勇椿 on 2020/10/26.
//
#include "../include/apue.h"

void
do_driver(char *driver){

    pid_t pid;
    int pipe[2];

    //create a full-duplex pipe to communicate with driver
    if (fd_pipe(pipe) < 0){
        err_sys("can't create stream pipe");
    }

    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid == 0){

        close(pipe[1]);
        //stdin for driver
        if (dup2(pipe[0], STDIN_FILENO) != STDIN_FILENO){
            err_sys("dup2 error to stdin");
        }
        //stdout for driver
        if (dup2(pipe[0], STDOUT_FILENO) != STDOUT_FILENO){
            err_sys("dup2 error to stdout");
        }
        if (pipe[0] != STDIN_FILENO && pipe[1] != STDOUT_FILENO){
            close(pipe[0]);
        }

        //leave stderr for driver alone
        execlp(driver, driver, (char *)0);
        err_sys("execlp error for %s", driver);
    } else{ //parent process

        close(pipe[0]);
        if (dup2(pipe[1], STDIN_FILENO) != STDIN_FILENO){
            err_sys("dup2 error to stdin");
        }
        if (dup2(pipe[1], STDOUT_FILENO) != STDOUT_FILENO){
            err_sys("dup2 error to stdout");
        }
        if (pipe[1] != STDIN_FILENO && pipe[1] != STDOUT_FILENO){
            close(pipe[1]);
        }
    }
}

