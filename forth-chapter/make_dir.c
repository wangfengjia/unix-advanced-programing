//
// Created by 王勇椿 on 2020/8/13.
//

#include <sys/stat.h>
#include <dirent.h>
#include "../include/apue.h"

#include <sys/stat.h>
#include "../include/apue.h"

void create(void);
void delete(void);
void read_dir(void);


int main(void){

//    create();
//    delete();
    read_dir();
    exit(0);
}

void create(void){

    if (mkdir("../dir/", S_IWUSR | S_IRUSR | S_IXUSR | S_IRGRP | S_IROTH) < 0){
        err_sys("make dir error");
    }
}

void delete(void){

    if (rmdir("../dir/") < 0){
        err_sys("rmdir error");
    }
}

void read_dir(void){

    DIR *dir;
    if ((dir = opendir("../file/")) == NULL){
        err_sys("open dir error");
    }

    struct dirent *dirent;
    if ((dirent = readdir(dir)) == NULL){
        err_sys("read dir error");
    }

    printf("file number: %lld\n", dirent->d_ino);
    printf("dir name: %s\n", dirent->d_name);
}