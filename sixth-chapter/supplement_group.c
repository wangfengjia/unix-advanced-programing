//
// Created by 王勇椿 on 2020/8/15.
//
//附属组

#include <unistd.h>
#include <netdb.h>
#include "../include/apue.h"

int main(void){

    int size = 10;
    gid_t gids[size];
    getgroups(size, gids);
    for (int i = 0; i < 10; i++){
        printf("group id: %u\n", gids[i]);
    }
}

