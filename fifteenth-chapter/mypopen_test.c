//
// Created by 王勇椿 on 2020/9/24.
//
#include "popen_implement.h"

#define PAGER "${PAGER:-more}"

int main(int argc, char *argv[]){

    char line[MAXLINE];
    FILE *fpin, *fpout;

    if (argc != 2){
        err_quit("usage: mypopen_test <pathname>");
    }
    if ((fpin = fopen(argv[1], "r")) == NULL){
        err_sys("can't open %s", argv[1]);
    }

    if ((fpout = my_popen(PAGER, "w")) == NULL){
        err_sys("my popen error");
    }

    while (fgets(line, MAXLINE, fpin) != NULL){
        if (fputs(line, fpout) == EOF){
            err_sys("fputs error to pipe");
        }
    }

    if (ferror(fpin)){
        err_sys("fgets error");
    }
    if (my_pclose(fpout) == -1){
        err_sys("my pclose error");
    }

    exit(0);
}

