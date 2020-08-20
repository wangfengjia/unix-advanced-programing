//
// Created by 王勇椿 on 2020/8/20.
//
#include "../include/my_apue.h"
#include "../include/apue.h"

int main(int argc, char *argv[]){

    int status;

    if (argc < 2){
        err_quit("command-line argument required");
    }

    if ((status = mysystem(argv[1])) < 0){
        err_sys("mysystem() error");
    }
    print_exit(status);

    exit(0);
}
