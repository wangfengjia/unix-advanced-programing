//
// Created by 王勇椿 on 2020/8/15.
//
//SingleUNIXSpecification为处理临时文件定义了另外两个函数：mkdtemp和mkstemp，它们是XSI的扩展部分。
//

#include "../include/apue.h"
#include <errno.h>

void make_temp(char *template);

int main(void){

    /**
     * 对于第一个模板，因为使用了数组，名字是在栈上分配的。但第二种情况使用的是指针，在这种情况下，只有指针
     * 自身驻留在栈上。编译器把字符串存放在可执行文件的只读段，当mkstemp函数试图修改字符串时，出现了段错误（segmentfault）。
     */
    char good_template[] = "/tmp/dirXXXXXX";
    char *bad_template = "/tmp/dirXXXXXX";

    printf("trying to create first temp file ...\n");
    make_temp(good_template);
    printf("trying to create second temp file ...\n");
    make_temp(bad_template);
}


void make_temp(char *template){

    int fd;
    struct stat buf;

    if ((fd = mkstemp(template)) < 0){
        err_sys("mkstemp error");
    }
    printf("temp name: %s\n", template);
    close(fd);

    errno = 0;
    if (stat(template, &buf) < 0){
        if (errno == ENOENT){
            printf("file doesn't exists\n");
        } else{
            err_sys("stat failed");
        }
    } else{
        printf("file exists\n");
        unlink(template);
    }

    if (errno != 0){
        perror("error:");
    }
}
