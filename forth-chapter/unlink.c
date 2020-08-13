//
// Created by 王勇椿 on 2020/8/13.
//

#include "../include/apue.h"
#include <fcntl.h>

int main(void){

    if (open("../file/foo.txt", O_RDWR) < 0){
        err_sys("open errors");
    }

    if (unlink("../file/foo.txt") < 0){
        err_sys("unlink errors");
    }

    printf("file unlinked\n");
    sleep(15);
    printf("done\n");
    exit(0);
}
