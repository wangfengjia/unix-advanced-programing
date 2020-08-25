//
// Created by 王勇椿 on 2020/8/24.
//

//需要有一种方法来通知内核哪一个进程组是前台进程组，这样终端设备驱动程序就能知道将终端输入和终端产生的信号发往何处

#include <unistd.h>
#include <fcntl.h>
#include "../include/apue.h"

int main(void){

    int fd;
    pid_t gid;

//    if ((fd = open("/dev/tty", O_WRONLY)) < 0){
//        err_sys("open error");
//    }

    //返回前台进程组ID
    if ((gid = tcgetpgrp(STDOUT_FILENO)) < 0){
        err_sys("tcgetpgrp() error");
    }

    printf("group id: %d\n", gid);
}
