//
// Created by 王勇椿 on 2020/8/11.
//

#include "../include/apue.h"
#include <sys/stat.h>
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(void){

    umask(0);
    if (creat("../file/foo.txt", RWRWRW) < 0){
        err_sys("create error for foo");
    }
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (creat("../file/bar.txt", RWRWRW) < 0){
        err_sys("create error for bar");
    }

    exit(0);
}

