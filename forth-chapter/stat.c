//
// Created by 王勇椿 on 2020/8/10.
//

#include "../include/apue.h"
#include <sys/stat.h>

void l_stat(void);
void l_file_type(void);

int main(void){

//    l_stat();
    l_file_type();
}

void l_stat(void){

    struct stat buf;
    char *pathname = "../file/sys_limit.txt";

    stat(pathname, &buf);
    printf("size: %ld\n", buf.st_size);
}

void l_file_type(void){


    struct stat buf;
    stat("../file/sys_limit.txt", &buf);

    mode_t mode = buf.st_mode;
    if (S_ISREG(mode)){
        printf("regular file");
    }
}


