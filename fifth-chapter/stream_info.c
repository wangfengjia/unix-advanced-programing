//
// Created by 王勇椿 on 2020/8/15.
//
//流的相关信息

#include "../include/apue.h"


void pr_stdio(const char *, FILE *);
int is_unbuffered(FILE *);
int is_linebuffered(FILE *);
int buffer_size(FILE *);


int main(void){

    FILE *fp;

    fputs("enter any character\n", stdout);
    if (getchar() == EOF){
        err_sys("getchar error");
    }
    fputs("one line to standard error\n", stderr);

    pr_stdio("stdin", stdin);
    pr_stdio("stdout", stdout);
    pr_stdio("stderr", stderr);

    if ((fp = fopen("/etc/passwd", "r")) == NULL){
        err_sys("fopen error");
    }

    if (getc(fp) == EOF){
        err_sys("getc error");
    }

    pr_stdio("/etc/passwd", fp);
    exit(0);
}

void pr_stdio(const char *name, FILE *fp){

    printf("stream = %s, ", name);
    if (is_unbuffered(fp)){
        printf("unbuffered");
    } else if (is_linebuffered(fp)){
        printf("line bufferered");
    } else{
        printf("fully buffered");
    }

    printf(", buffer size = %d\n", buffer_size(fp));
}

int is_unbuffered(FILE *fp){
    return (fp->_flags & __SNBF);
}

int is_linebuffered(FILE *fp){
    return (fp->_flags & __SLBF);
}

int buffer_size(FILE *fp){

    return fp->_bf._size;
}

