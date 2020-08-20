//
// Created by 王勇椿 on 2020/8/19.
//
#include "../include/apue.h"

int main(int argc, char *argv[]){

    int i;
    for (i = 0; i < argc; i++){
        printf("argc[%d]: %s\n", i, argv[i]);
    }
}

