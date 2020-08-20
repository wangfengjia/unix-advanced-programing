//
// Created by 王勇椿 on 2020/8/20.
//

#include "../include/my_apue.h"
#include "../include/apue.h"
#include <sys/wait.h>

int main(void){

    int status;

    if ((status = mysystem("date")) < 0){
        err_sys("mysystem() error");
    }
    print_exit(status);

    if ((status = mysystem("nosuchcommand")) < 0){
        err_sys("mysystem() error");
    }
    print_exit(status);

    if ((status = mysystem("who; exit 44")) < 0){
        err_sys("mysystem() error");
    }
    print_exit(status);

    exit(0);
}



