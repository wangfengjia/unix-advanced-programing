//
// Created by 王勇椿 on 2020/9/24.
//
/**
 * 进程通信方式-管道
 * 1.历史上管道时半双工的(数据只能在一个方向上流动)。现在某些系统提供全双工(数据可以在两个方向上流动)管道，但是为了可移植性，我们不可以预先假定系统支持全双工管道
 * 2.管道只能在具有公共祖先的两个进程间使用
 * 3.数据需要通过内核在管道中流动
 * 4.管道有两端(读端和写端)，对两端的不同操作决定了数据流的方向。比如fork之后，想要数据流的方向是父进程到子进程，则需要关闭父进程的读端和关闭子进程的写端
 */
//例子:创建父进程到子进程的管道
#include "../include/apue.h"

int
main(void){

    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];

    if (pipe(fd) < 0){
        err_sys("pipe error");
    }

    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid > 0){ //parent process
        close(fd[0]);
        write(fd[1], "hello world\n", 12);
    } else{ //child process
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
    }

    exit(0);
}
































