//
// Created by 王勇椿 on 2020/9/2.
//

#include "../include/apue.h"

static void ssig_int(int);
static void ssig_chld(int);

int main(void){

    if (signal(SIGINT, ssig_int) == SIG_ERR){
        err_sys("signal(SIGINT) error");
    }
    if (signal(SIGCHLD, ssig_chld) == SIG_ERR){
        err_sys("signal(SIGCHLD) error");
    }

    if (system("/bin/ed") < 0){
        err_sys("system() error");
    }

    exit(0);

}

static void ssig_int(int signo){
    printf("caught SIGINT \n");
}

static void ssig_chld(int signo){
    printf("caught SIGCHLD\n");
}
