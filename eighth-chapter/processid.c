//
// Created by 王勇椿 on 2020/8/17.
//
//进程唯一标识，进程ID，非负整数

#include <unistd.h>
#include "../include/apue.h"

int main(void){

    pid_t pid = getpid();
    pid_t parent_process_id = getppid();


    printf("process id: %d\n", pid);
    printf("parent process id: %d\n", parent_process_id);
}

