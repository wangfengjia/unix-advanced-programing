//
// Created by 王勇椿 on 2020/8/26.
//

#include "../include/apue.h"
#include <stdbool.h>

static void sig_user(int); //one handler for two signal

int main(void){

    if (signal(SIGUSR1, sig_user) == SIG_ERR){
        err_sys("can't catch sigusr1\n");
    }
    if (signal(SIGUSR2, sig_user) == SIG_ERR){
        err_sys("can't catch sigusr2\n");
    }

    while (true){
        pause();
    }
}


static void sig_user(int signo){

    if (signo == SIGUSR1){
        printf("received SIGUSR1\n");
    } else if (signo == SIGUSR2){
        printf("received SIGUSR2\n");
    } else{

        err_dump("received signal %d\n", signo);
    }
}

