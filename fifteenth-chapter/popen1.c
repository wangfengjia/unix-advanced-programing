//
// Created by 王勇椿 on 2020/9/24.
//
//标准I/O库提供两个函数popen和pclose函数，这两个函数实现的操作是:创建一个管道，fork一个子进程，关闭未使用的管道端，执行一个shell运行命令，然后等待命令终止

//例子:分页显示已产生的输出的第二个版本
#include "../include/apue.h"
#include <sys/wait.h>

#define PAGER "${PAGER:-more}" //enviroment variable, or default

int
main(int argc, char *argv[]){

    char line[MAXLINE];
    FILE *fpin, *fpout;

    if (argc != 2){
        err_quit("usage: popen1 <pathname>");
    }
    if ((fpin = fopen(argv[1], "r")) == NULL){
        err_sys("can't open %s", argv[1]);
    }
    if ((fpout = popen(PAGER, "w")) == NULL){
        err_sys("popen error");
    }

    //copy argv[1] to pager
    while (fgets(line, MAXLINE, fpin) != NULL){
        if (fputs(line, fpout) == EOF){
            err_sys("fputs error to pipe");
        }
    }

    if (ferror(fpin)){
        err_sys("fgets error");
    }
    if (pclose(fpout) == -1){
        err_sys("pclose error");
    }

    exit(0);
}