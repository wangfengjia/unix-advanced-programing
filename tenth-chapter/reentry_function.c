//
// Created by 王勇椿 on 2020/8/27.
//

//可重入函数(在进程的正常指令序列和信号处理程序中调用此函数，能够产生预期的结果)

#include "../include/apue.h"
#include <pwd.h>
#include <stdbool.h>

static void my_alarm(int);

int main(void){

    struct passwd *ptr;

    signal(SIGALRM, my_alarm);
    alarm(1);

    while (true){
        if ((ptr = getpwnam("vagrant")) == NULL){
            err_sys("getpwnam error");
        }
        if (strcmp(ptr->pw_name, "vagrant") != 0){
            printf("return value corrupted, pw_name = %s\n", ptr->pw_name);
        }
    }
}

static void my_alarm(int signo){

    struct passwd *rootptr;

    printf("in signal handler\n");
    if ((rootptr = getpwnam("root")) == NULL){
        err_sys("getpwnam(root) error");
    }
    alarm(1);
}