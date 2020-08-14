//
// Created by 王勇椿 on 2020/8/14.
//
//为每个命令行打印设备号

#include <sys/types.h>
#include "../include/apue.h"

int main(int argc, char *argv[]){

    int i;
    struct stat buf;

    for (i = 1; i < argc; i++){

        printf("%s:", argv[i]);
        if (stat(argv[1], &buf) < 0){
            err_ret("stat error");
            continue;
        }
        printf("dev = %d/%d", major(buf.st_dev), minor(buf.st_dev));
        if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)){
            printf(" (%s) rdev = %d/%d", (S_ISCHR(buf.st_mode)) ? "character" : "block", major(buf.st_rdev), minor(buf.st_rdev));
        }

        printf("\n");
    }
    exit(0);
}

