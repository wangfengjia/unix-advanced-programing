//
// Created by 王勇椿 on 2020/8/15.
//

#include "../include/apue.h"

#define BUFFER_LENGTH 25

void my_sprintf(void);

int main(void){

    my_sprintf();
}


void my_sprintf(void){

    char buf[BUFFER_LENGTH];
    snprintf(buf, BUFFER_LENGTH, "%d-%d-%d %d:%d:%d", 2020, 8, 15, 10, 20, 59);
    printf("buf: %s\n", buf);

    FILE *fp;
    if ((fp = fopen("../file/rename.txt", "a")) == NULL){
        err_sys("fopen error");
    }

    char content[BUFFER_LENGTH] = {'a', 'b', 'c', 'd', 'w', 'e'};
    if (fputs(content, fp) == EOF){
        err_sys("content: %s\n", buf);
    }

    if (ferror(fp)){
        err_sys("input error");
    }
}
