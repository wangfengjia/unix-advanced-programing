//
// Created by 王勇椿 on 2020/8/12.
//

#include "../include/apue.h"
#include <unistd.h>

void link_count();
int main(void){

//    if (link("../file/link2.txt", "../file/sys_limit.txt") < 0){
//        err_quit("link error");
//    }
//
//    if (link("../file/link2.txt", "../file/link.txt") < 0){
//        err_quit("link error");
//    }

//    if (unlink("../file/link2.txt") < 0){
//        err_sys("unlink error");
//    }
//
    link_count();
    exit(0);
}

void link_count(){

    struct stat stat_buf;
    if (stat("../file/sys_limit.txt", &stat_buf) < 0){
        err_sys("stat error");
    }

    printf("link count: %d\n", stat_buf.st_nlink);
}
