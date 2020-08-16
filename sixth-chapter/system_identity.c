//
// Created by 王勇椿 on 2020/8/16.
//

//系统标识-主机和操作系统相关信息
#include <sys/utsname.h>
#include "../include/apue.h"

int main(void){

    struct utsname name;
    if (uname(&name) < 0){
        err_sys("uname error");
    }

    printf("sysname: %s, release: %s, version: %s, machine: %s", name.sysname, name.release, name.version, name.machine);
}



