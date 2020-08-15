//
// Created by 王勇椿 on 2020/8/15.
//
//定位流，流的位置

#include "../include/apue.h"

int main(void){

    FILE *fp;
    if ((fp = fopen("../file/rename.txt", "a")) == NULL){
        err_sys("fopen error");
    }

    long pos = ftell(fp);
    printf("stream pos: %ld\n", pos);

    char buf[10] = "\nABCDEFGH";
    if (fputs(buf, fp) == EOF){
        err_sys("fputs error");
    }

    if (ferror(fp)){
        err_sys("input error");
    }

    long newpos = ftell(fp);
    printf("stream pos: %ld\n", newpos);

    if (fseek(fp, 0, SEEK_SET) < 0){
        err_sys("fseek error");
    }
    long newpopos = ftell(fp);
    printf("stream pos: %ld\n", newpopos);

    if (fputs(buf, fp) == EOF){
        err_sys("fputs error");
    }
}
