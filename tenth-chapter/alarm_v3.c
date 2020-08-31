//
// Created by 王勇椿 on 2020/8/31.
//

//alarm函数除了用来实现sleep函数外，还可以用来对可能的阻塞操作设置时间上限
#include <setjmp.h>
#include "../include/apue.h"

static void sig_alarm(int);
static jmp_buf env_alarm;

int main(void){

    int n;
    char line[MAXLINE];

    if (signal(SIGALRM, sig_alarm) == SIG_ERR){
        err_sys("signal(SIGALARM) error");
    }

    if (setjmp(env_alarm) != 0){
        err_quit("read timeout");
    }

    alarm(5);
    if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0){
        err_sys("read error");
    }
    alarm(0);

    write(STDOUT_FILENO, line, n);
    exit(0);
}

static void sig_alarm(int signo){

    longjmp(env_alarm, 1);

}