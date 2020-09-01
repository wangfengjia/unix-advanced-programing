//
// Created by 王勇椿 on 2020/8/31.
//
//打印调用进程的信号屏蔽字的信号名

#include "../include/apue.h"
#include <errno.h>

void print_mask(const char *str);


int main(void){

    print_mask("print process cmask");
}
void print_mask(const char *str){

    sigset_t sigset;
    int error_save;

    error_save = errno;
    if (sigprocmask(0, NULL, &sigset) < 0){
        err_ret("sigprocmask error");
    } else{

        printf("%s", str);
        if (sigismember(&sigset, SIGINT)){
            printf(" SIGINT");
        }
        if (sigismember(&sigset, SIGQUIT)){
            printf(" SIGQUIT");
        }
        if (sigismember(&sigset, SIGUSR1)){
            printf(" SIGUSR1");
        }
        if (sigismember(&sigset, SIGALRM)){
            printf(" SIGALARM");
        }

        printf("\n");
    }

    errno = error_save;
}

