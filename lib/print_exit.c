//
// Created by 王勇椿 on 2020/8/20.
//

#include <sys/wait.h>
#include "../include/apue.h"
#include "../include/my_apue.h"

void print_exit(int status){

    if (WIFEXITED(status)){
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)){
        printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
               WCOREDUMP(status) ? " (core file generated)" : "");
#else
        "");
#endif
    } else if (WIFSTOPPED(status)){
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
    }
}