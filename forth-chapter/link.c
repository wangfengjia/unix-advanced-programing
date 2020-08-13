//
// Created by 王勇椿 on 2020/8/12.
//

#include "../include/apue.h"
#include <unistd.h>


int main(void){

    if (link("../file/sys_limit.txt", "../file/link.txt") < 0){
        err_quit("link error");
    }
}
