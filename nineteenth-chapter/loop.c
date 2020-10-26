//
// Created by 王勇椿 on 2020/10/26.
//
#include "../include/apue.h"
#include "loop.h"
#include <stdbool.h>

static void sig_term(int);
static volatile sig_atomic_t sigcaught; //set by signal handler

void
loop(int ptym, int ignoreof){

    pid_t pid;
    int nread;
    char buf[BUFFSIZE];

    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid == 0){ //child copy stdin to ptym
        while (true){
            if ((nread = read(STDIN_FILENO, buf, BUFFSIZE)) < 0){
                err_sys("read error from stdin");
            } else if (nread == 0){
                break; //EOF on stdin means we're done
            }

            if (write(ptym, buf, nread) != nread){
                err_sys("write error to master pty");
            }
        }

        /**
         * We always terminate when we encounter an EOF on stdin, but we notify the parent only if ignoreeof is 0
         */
         if (ignoreof == 0){
             kill(getppid(), SIGTERM); //notify parent
         }
         exit(0);
    }

    //only parent process execute here
    if (signal_intr(SIGTERM, sig_term) == SIG_ERR){
        err_sys("signal_intr error for SIGTERM");
    }

    while (true){
        if ((nread = read(ptym, buf, BUFFSIZE)) < 0){
            break; //signal caught,error or EOF
        }
        if (writen(STDOUT_FILENO, buf, nread) != nread){
            err_sys("writen error to stdout");
        }
    }

    /**
     * There are three way to get here:sig_term() below caught the SIGTERM from child, we read an EOF on the pty master(
     * which means we have to signal the child to stop), or an error
     */
     if (sigcaught == 0){ //tell child if it didn't send us the signal
        kill(pid, SIGTERM);
     }
}

/**
 * The child sends us SIGTERM when it gets EOF on pty slave or when read() fails. We probably interrupted the read() of ptym
 * @param signo
 */
static void
sig_term(int signo){

    sigcaught = 1; //just set flag and return

}

