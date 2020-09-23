//
// Created by 王勇椿 on 2020/9/22.
//
//将一个文件从一个格式翻译为另外一个格式(使用传统I/O接口)
#include "../include/apue.h"
#include <ctype.h>
#include <fcntl.h>

#define BSZ 4096

unsigned char buf[BSZ];

unsigned char translate(unsigned char);

unsigned char
translate(unsigned char c){

    if (isalpha(c)){
        if (c >= 'n'){
            c -= 13;
        } else if (c >= 'a'){
            c += 13;
        } else if (c >= 'N'){
            c -= 13;
        } else{
            c += 13;
        }
    }

    return c;
}

int
main(int argc, char *argv[]){

    int input_fd, output_fd, i, n, nw;

    if (argc != 3){
        err_quit("usage: rot13 infile outfile");
    }
    if ((input_fd = open(argv[1], O_RDONLY)) < 0){
        err_sys("can't open %s", argv[1]);
    }
    if ((output_fd = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, FILE_MODE)) < 0){
        err_sys("can't create %s", argv[2]);
    }

    while ((n = read(input_fd, buf, BUFSIZ)) > 0){
        for (i = 0; i < n; i++){
            buf[i] = translate(buf[i]);
        }

        if ((nw = write(output_fd, buf, n)) != n){
            if (nw < 0){
                err_sys("write failed");
            } else{
                err_quit("short write (%d/%d)", nw, n);
            }
        }
    }

    fsync(output_fd);
    exit(0);
}






























