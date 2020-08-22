//
// Created by 王勇椿 on 2020/8/20.
//

#include "../include/apue.h"
#include <sys/acct.h>

int main(void){


    pid_t pid;

    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid != 0){ //parent process
        sleep(2);
        exit(2);
    }

    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid != 0){ // first child process
        sleep(4);
        abort(); //terminate with core dump
    }

    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid != 0){ //second child process
        execl("/bin/dd", "dd", "if=/etc/passwd", "of=/dev/null", NULL);
        exit(7); //shouldn't get here
    }

    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid != 0){ //third child process
        sleep(8);
        exit(0); // normal exit
    }

    //forth child process
    sleep(6);
    kill(getpid(), SIGKILL);
    exit(0);
}