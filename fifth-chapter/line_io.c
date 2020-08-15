//
// Created by 王勇椿 on 2020/8/14.
//
//一次io读写一行

#include "../include/apue.h"


void line_read(void);
void line_write(void);

#define LINE_LENGTH 15

int main(void){

//    line_read();
    line_write();
    exit(0);
}

void line_read(void){

    FILE *fp;
    if ((fp = fopen("../file/rename.txt", "r")) == NULL){
        err_sys("fopen error");
    }

    char line[LINE_LENGTH];
    while (fgets(line, LINE_LENGTH, fp) != NULL){
        printf("content: %s\n", line);
    }
}

void line_write(void){


    FILE *fp;
    if ((fp = fopen("../file/rename.txt", "a")) == NULL){
        err_sys("fopen file");
    }

    char content[LINE_LENGTH] = "ABCEDFABCEDF";
    for (int i = 0; i < 2; ++i) {
        if (fputs(content, fp) == EOF){
            err_sys("fputs error");
        }
    }
}




