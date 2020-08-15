//
// Created by 王勇椿 on 2020/8/14.
//
//打开流

#include "../include/apue.h"

int main(void){

    FILE *fp;
    if ((fp = fopen("../file/rename.txt", "w")) == NULL){
        err_sys("fopen error");
    }
}

