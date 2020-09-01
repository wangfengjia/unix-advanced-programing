//
// Created by 王勇椿 on 2020/9/1.
//

#include "mysignal.h"

static void sig_quit(int);


int main(void){

    if (mysignal_v2(SIGQUIT, sig_quit) == SIG_ERR){
        err_sys("mysignal v2 error");
    }

    sleep(5);
}

static void sig_quit(int signo){

    printf("mysignal v2 sig quit");
}

