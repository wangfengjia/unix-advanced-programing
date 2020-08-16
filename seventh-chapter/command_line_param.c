//
// Created by 王勇椿 on 2020/8/16.
//

#include "../include/apue.h"

int main(int argc, char *argv[]){

    //处理命令行参数的两种方法
    int i;
    for (i = 0; i < argc; i++){
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    //由于IOS C和POSIX.1要求argv[argc]是一个空指针，所以可以判断参数数组元素是否为空指针来判断处理命令行参数的终止条件
    int j;
    for (j = 0; argv[j] != NULL; j++){
        printf("argv[%d]: %s\n", j, argv[j]);
    }

    exit(0);
}
