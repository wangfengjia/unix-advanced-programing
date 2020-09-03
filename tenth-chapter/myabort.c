//
// Created by 王勇椿 on 2020/9/2.
//

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>


void myabort(void);

int main(void){

    myabort();
}
//POSIX-style abort() function
void myabort(void){

    sigset_t mask;
    struct sigaction action;

    sigaction(SIGABRT, NULL, &action);
    if (action.__sigaction_u.__sa_handler == SIG_IGN){
        action.__sigaction_u.__sa_handler = SIG_DFL;
        sigaction(SIGABRT, &action, NULL);
    }

    if (action.__sigaction_u.__sa_handler == SIG_DFL){
        fflush(NULL); //flush all open stdio stream
    }

    //caller can't block SIGABRT;make sure it is unblocked
    sigfillset(&mask);
    sigdelset(&mask, SIGABRT); // mask has only SIGABRT turn off

    sigprocmask(SIG_SETMASK, &mask, NULL);
    kill(getpid(), SIGABRT);

    //If we're here,process caught SIGABRT and returned
    fflush(NULL);
    action.__sigaction_u.__sa_handler = SIG_DFL;
    sigaction(SIGABRT, &action, NULL); //reset to default
    sigprocmask(SIG_SETMASK, &mask, NULL);
    kill(getpid(), SIGABRT);
    exit(1); // this should never be executed
}

