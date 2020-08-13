//
// Created by 王勇椿 on 2020/8/13.
//

#include "../include/apue.h"
#include <stdio.h>

int main(void){

    if (rename("/Users/wangyongchun/www/study/c/unix-advanced-programing/forth-chapter/rename.txt", "/Users/wangyongchun/www/study/c/unix-advanced-programing/file/rename.txt") < 0){
        err_sys("rename error");
    }

    exit(0);
}
