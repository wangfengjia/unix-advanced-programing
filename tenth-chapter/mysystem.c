//
// Created by 王勇椿 on 2020/9/2.
//

#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stddef.h>
#include "mysystem.h"


int mysystem(const char *cmdstring){

    pid_t pid;
    int status;
    struct sigaction ignore, saveintr, savequit;
    sigset_t chldmask, savemask;
    errno = 0;

    if (cmdstring == NULL){
        return 1;
    }

    //ignore SIGINT and SIGQUIT
#ifdef LINUX
        ignore.sa_handler = SIG_IGN;
#elif defined(MACOS)
        ignore.__sigaction_u.__sa_handler = SIG_IGN;
#endif
    sigemptyset(&ignore.sa_mask);
    ignore.sa_flags = 0;

    if (sigaction(SIGINT, &ignore, &saveintr) < 0){
        return -1;
    }
    if (sigaction(SIGINT, &ignore, &savequit) < 0){
        return -1;
    }
    //now block SIGCHLD
    sigemptyset(&chldmask);
    sigaddset(&chldmask, SIGCHLD);
    if (sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0){
        return -1;
    }

    if ((pid = fork()) < 0){
        status = -1;
    } else if (pid == 0){
        //restore previous signal action && reset signal mask
        sigaction(SIGINT, &saveintr, NULL);
        sigaction(SIGQUIT, &savequit, NULL);
        sigprocmask(SIG_SETMASK, &savemask, NULL);
        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        _exit(127); //exec error
    } else{
        while (waitpid(pid, &status, 0) < 0){
            if (errno != EINTR){
                status = -1;
                break;
            }
        }
    }

    //restore previous signal action && reset signal mask
    if (sigaction(SIGINT, &saveintr, NULL) < 0){
        return -1;
    }
    if (sigaction(SIGQUIT, &savequit, NULL) < 0){
        return -1;
    }
    if (sigprocmask(SIG_SETMASK, &savemask, NULL) < 0){
        return -1;
    }

    return status;
}

