//
// Created by 王勇椿 on 2020/9/2.
//

#include "../include/apue.h"

int main(void){

    sleep(10);
    printf("process id: %ld, parent process id: %ld\n", (long)getpid(), (long)getppid());
}

