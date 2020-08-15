//
// Created by 王勇椿 on 2020/8/15.
//

//创建临时文件

#include "../include/apue.h"

int main(void){

    char name[L_tmpnam], line[MAXLINE];
    FILE *fp;

    printf("%s\n", tmpnam(NULL));

    tmpnam(name);
    printf("%s\n", name);

    if ((fp = tmpfile()) == NULL){
        err_sys("tmpfile error");
    }
    fputs("one line for output\n", fp);
    rewind(fp);
    if (fgets(line, sizeof(line), fp) == NULL){
        err_sys("fgets error");
    }
    tempnam()
    fputs(line, stdout);
    exit(0);
}

