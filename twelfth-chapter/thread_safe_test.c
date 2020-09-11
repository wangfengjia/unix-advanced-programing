//
// Created by 王勇椿 on 2020/9/10.
//

#include "thread_safe.h"
#include "../include/apue.h"


int main(void){

    char home[100];

    getenv_r("HOME", home, 100);
    printf("HOME: %s\n", home);
}