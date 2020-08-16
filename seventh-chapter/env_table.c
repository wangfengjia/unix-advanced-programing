//
// Created by 王勇椿 on 2020/8/16.
//

//环境表

#include "../include/apue.h"
#include <stdlib.h>

extern char **environ;

int main(void){

    char *home = getenv("HOME");
    printf("home: %s\n", home);
    
    for (; *environ != NULL; environ++){
        printf("env param: %s\n", *environ);
    }
}

