//
// Created by 王勇椿 on 2020/9/17.
//

#include "daemonize.h"
#include "../include/apue.h"
#include "singleton_daemon_process.h"

int main(void){

    if (already_running() != 0){
        err_sys("daemon process already running");
    }
    mydaemonize("daemonize_test");
    sleep(360);
}

