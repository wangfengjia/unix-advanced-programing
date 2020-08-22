//
// Created by 王勇椿 on 2020/8/21.
//
#include <unistd.h>
#include "../include/apue.h"

int main(void){

    char *login_name = getlogin();
    printf("login name: %s\n", login_name);
}
