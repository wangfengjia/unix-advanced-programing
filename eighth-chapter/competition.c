//
// Created by 王勇椿 on 2020/8/18.
//
//当多个进程试图对共享数据处理时，最后的结果取决于进程的运行顺序时，我们就认为发生了竞争条件

#include "../include/apue.h"
#include <unistd.h>

static void charatatime(char *);

int main(void){

    pid_t pid;
    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid == 0){
        charatatime("output from child\n");
    } else{
        charatatime("output from parent\n");
    }

    exit(0);
}


static void charatatime(char *str){

    char *ptr;
    int c;

    //set unbuffred
    setbuf(stdout, NULL);
    for (ptr = str; ptr < str + strlen(str); ptr++){
        putc(*ptr, stdout);
    }

//    for (ptr = str; (c = *ptr) != 0; ptr++){
//        putc(c, stdout);
//    }
}

