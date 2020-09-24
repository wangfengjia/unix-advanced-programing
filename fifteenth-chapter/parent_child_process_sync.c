//
// Created by 王勇椿 on 2020/9/24.
//
//图10-24提供了一个使用信号的实现，这边提供一个使用管道的实现
#include "../include/apue.h"
#include "parent_child_process_sync.h"

static int pfd1[2], pfd2[2];

void
TELL_WAIT_V2(void){

    if (pipe(pfd1) < 0 || pipe(pfd2) < 0){
        err_sys("pipe error");
    }
}

//子进程到父进程的管道
void
TELL_PARENT_V2(void){

    if (write(pfd2[1], "c", 1) != 1){
        err_sys("write error");
    }
}

void
WAIT_CHILD_V2(void){

    char c;
    if (read(pfd2[0], &c, 1) != 1){
        err_sys("read error");
    }

    if (c != 'c'){
        err_quit("WAIT_CHILD: incorrect data");
    }
}

//父进程到子进程的管道
void
TELL_CHILD_V2(void){

    if (write(pfd1[1], "p", 1) != 1){
        err_sys("write error");
    }
}
void
WAIT_PARENT_V2(void){

    char c;

    if (read(pfd1[0], &c, 1) != 1){
        err_sys("read error");
    }

    if (c != 'p'){
        err_quit("WAIT_PARENT: incorrect data");
    }
}

void
TELL_CHILD_V2(void){

    if (write())
}

