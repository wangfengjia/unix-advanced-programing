//
// Created by 王勇椿 on 2020/9/1.
//
#include "mysignal.h"

static void sig_quit(int);

int main(void){


    if (mysignal(SIGQUIT, sig_quit) == SIG_ERR){
        err_sys("mysignal error");
    }

    sleep(5);
}

static void sig_quit(int signo){

    printf("signal quit");
}
