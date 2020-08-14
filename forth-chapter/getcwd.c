//
// Created by 王勇椿 on 2020/8/13.
//获取当前工作目录

#include "../include/apue.h"

int main(void){

    char *ptr;
    size_t size;
    if (chdir("/Users/wangyongchun/www/study/c/apue.3e") < 0){
        err_sys("chdir error");
    }

    ptr = path_alloc(&size);
    if (getcwd(ptr, size) == NULL){
        err_sys("get cwd error");
    }

    printf("cwd: %s\n", ptr);
    exit(0);
}

