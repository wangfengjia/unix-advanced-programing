//
// Created by 王勇椿 on 2020/9/17.
//

#include "daemonize.h"
#include "../include/apue.h"
#include "singleton_daemon_process.h"

int main(void){


    mydaemonize("daemonize_test");
    if (already_running()){
        err_sys("daemon process already running");
    }
    sleep(360);
}

