//
// Created by 王勇椿 on 2020/8/25.
//
//孤儿进程组:这个进程组中的每个进程的父进程时这个进程组的成员或者不是该组所属会话的成员

#include "../include/apue.h"
#include <errno.h>

static void sig_hup(int);
static void pr_ids(char *);

int main(void){

    char c;
    pid_t pid;

    pr_ids("parent");
    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid > 0){
        sleep(5); //sleep to let children stop itself
    } else{
        pr_ids("children");
        signal(SIGHUP, sig_hup);
        kill(getpid(), SIGTSTP); //stop child process
        pr_ids("children");
        errno = 0;
        if (read(STDIN_FILENO, &c, 1) != 1){
            printf("read error %d on controlling TTY\n", errno);
        }
    }
}

static void sig_hup(int signo){

    printf("SIGHUP received, pid = %ld\n", (long)getpid());
}

static void pr_ids(char *name){

    printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tgrp = %ld\n", name, (long)getpid(), (long)getppid(), (long)getpgrp(), (long)tcgetpgrp(STDIN_FILENO));
    fflush(stdout);
}

