//
// Created by 王勇椿 on 2020/9/23.
//
//存储映射I/O复制文件
#include "../include/apue.h"
#include <fcntl.h>
#include <sys/mman.h>

#define COPYINCR (1024 * 1024 * 1024) //1GB

int
main(int argc, char *argv[]){

    int input_fd, output_fd;
    void *src, *dst;
    size_t copysz;
    struct stat sbuf;
    off_t off = 0;

    if (argc != 3){
        err_quit("usage: %s <fromfile> <tofile>", argv[0]);
    }
    if ((input_fd = open(argv[1], O_RDONLY)) < 0){
        err_sys("can't open %s for reading", argv[1]);
    }
    if ((output_fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0){
        err_sys("can't create %s for writing", argv[2]);
    }

    //input file size
    if (fstat(input_fd, &sbuf) < 0){
        err_sys("fstat error");
    }
    //set output file size
    if (ftruncate(output_fd, sbuf.st_size) < 0){
        err_sys("ftruncate error");
    }

    while (sbuf.st_size > off){
        if ((sbuf.st_size - off) > COPYINCR){
            copysz = COPYINCR;
        } else{
            copysz = sbuf.st_size - off;
        }

        if ((src = mmap(0, copysz, PROT_READ, MAP_SHARED, input_fd, off)) == MAP_FAILED){
            err_sys("mmap error for input");
        }
        if ((dst = mmap(0, copysz, PROT_READ | PROT_WRITE, MAP_SHARED, output_fd, off)) == MAP_FAILED){
            err_sys("mmap error for output");
        }

        //do the file copy
        memcpy(dst, src, copysz);
        //解除原有的存储映射区映射
        munmap(src, copysz);
        munmap(dst, copysz);
        off += copysz;
    }
}
