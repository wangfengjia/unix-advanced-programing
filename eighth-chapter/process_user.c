//
// Created by 王勇椿 on 2020/8/19.
//

#include <unistd.h>
#include "../include/apue.h"

int main(void){

    uid_t uid = getuid();
    gid_t gid = getgid();
    printf("uid: %d, gid: %d\n", uid, gid);

}

