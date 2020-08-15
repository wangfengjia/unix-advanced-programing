//
// Created by 王勇椿 on 2020/8/15.
//
//只在linux3.2.0下支持内存流

#include "../include/apue.h"

#define BSZ 48

int main(void){

    FILE *fp;
    char buf[BSZ];

    memset(buf, 'a', BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'X';
    if ((fp = fmemopen(buf, BSZ, "w+")) == NULL){
        err_sys("fmmopen error");
    }
    printf("initial buffer contents: %s\n", buf);
    fprintf(fp, "hello, world");
    printf("before flush: %s\n", buf);
    fflush(fp);
    printf("after flush: %s\n", buf);
    printf("length of string in buf = %ld\n", (long)strlen(buf));


    memset(buf, 'b', BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'X';
    fprintf(fp, "hello, world");
    fseek(fp, 0, SEEK_SET);
    printf("after fseek: %s\n", buf);
    printf("length of string in buf = %ld\n", (long)strlen(buf));

    memset(buf, 'c', BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'X';
    fprintf(fp, "hello, world");
    fclose(fp);
    printf("after close: %s\n", buf);
    printf("length of string in buf = %ld\n", (long)strlen(buf));

    exit(0);
}
