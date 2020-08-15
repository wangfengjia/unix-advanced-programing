//
// Created by 王勇椿 on 2020/8/14.
//
//一次读写一个字符

#include "../include/apue.h"

void my_read(void);
void my_write(void);

int main(void){

    my_read();
//    my_write();
}

void my_read(void){

    FILE *fp;

    if ((fp = fopen("../file/rename.txt", "r")) == NULL){
        err_sys("fopen file error");
    }

    int ch;
    char chs[10];
    int i = 0;
    while ((ch = fgetc(fp)) != EOF){
        chs[i++] = (char)ch;
    }

    printf("first read content: %s\n", chs);
    //把上面读出的字符放回流中
//    for (; i >= 0; i--){
//        if (ungetc(chs[--i], fp) == EOF){
//            err_sys("ungetc error");
//        }
//    }
    for(int j = 0; j < i; j++){
        if (ungetc(chs[j], fp) == EOF){
            err_sys("ungetc error");
        }
    }

    //再读一次
    int j = 0;
    while ((ch = fgetc(fp)) != EOF){
        chs[j++] = (char)ch;
    }

    printf("second read content: %s\n", chs);
}

void my_write(void){

    FILE *fp;
    if ((fp = fopen("../file/rename.txt", "a")) == NULL){
        err_sys("fopen file error");
    }

    char content[10] = "ABCEDF";
    char *ptr = content;
    while (*ptr != 0){
        if (putc(*ptr, fp) == EOF){
            err_sys("putc error");
        }
        ptr++;
    }
}

