//
// Created by 王勇椿 on 2020/9/25.
//例子:向标准输出写一个提示，然后从标准输入读一行，可以使用popen函数，可以在应用程序和输入之间插入一个程序以便对输入进行变换处理(对输入进行的变换是路径名扩充)

#include "../include/apue.h"
#include <sys/wait.h>
#include <stdbool.h>

int
main(void){

    char line[MAXLINE];
    FILE *fpin;

    if ((fpin = popen("/home/vagrant/c-learn/unix-advanced-programing/fifteenth-chapter/myuclc", "r")) == NULL){
        err_sys("popen error");
    }

    while (true){
        //因为标准输出是行缓冲，而提示并不包含换行符，所以在写了提示之后，需要调用fflush
        fputs("prompt> ", stdout);
        fflush(stdout);
        //read from pipe
        if (fgets(line, MAXLINE, fpin) == NULL){
            break;
        }
        if (fputs(line, stdout) == EOF){
            err_sys("fputs error to pipe");
        }
    }

    if (pclose(fpin) == -1){
        err_sys("pclose error");
    }
    putchar('\n');
    exit(0);
}

