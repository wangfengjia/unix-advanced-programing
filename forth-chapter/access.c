//
// Created by 王勇椿 on 2020/8/11.
//
//按照实际用户ID和实际组ID进行访问权限测试

#include <unistd.h>
#include "../include/apue.h"
#include <fcntl.h>

int main(int argc, char *argv[]){

    if (argc != 2){
        err_quit("usage: access <pathname>");
    }

    if (access(argv[1], R_OK) < 0){
        err_ret("access for error %s", argv[1]);
    } else{
        printf("read access ok\n");
    }

    if (open(argv[1], O_RDONLY) < 0){
        err_ret("open error for %s", argv[1]);
    } else{
        printf("open for reading ok\n");
    }

    exit(0);
}

