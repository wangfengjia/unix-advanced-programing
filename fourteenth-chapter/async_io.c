//
// Created by 王勇椿 on 2020/9/22.
//
//将文件从一个格式翻译成另一个格式(使用异步I/O接口)
#include "../include/apue.h"
#include <ctype.h>
#include <fcntl.h>
#include <aio.h>
#include <errno.h>
#include <stdbool.h>

#define BSZ 4096
#define NBUF 8

enum rwop{
    UNUSED = 0,
    READ_PENDING = 1,
    WRITE_PENDING = 2
};

struct buf{
    enum rwop op;
    int last;
    struct aiocb aiocb;
    unsigned char data[BSZ];
};

struct buf bufs[NBUF];
unsigned char translate(unsigned char);

unsigned char translate(unsigned char c){

    if (isalpha(c)){
        if (c >= 'n'){
            c -=13;
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

    int input_fd, output_fd, i, j, n, err, numop;
    struct stat statbuf;
    const struct aiocb *aiolist[NBUF];
    off_t off = 0;

    if (argc != 3){
        err_quit("usage: rot13 infile outfile");
    }
    if ((input_fd = open(argv[1], O_RDONLY)) < 0){
        err_sys("can't open %s", argv[1]);
    }
    if ((output_fd = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, FILE_MODE)) < 0){
        err_sys("can't create %s", argv[2]);
    }

    if (fstat(input_fd, &statbuf) < 0){
        err_sys("fstat failed");
    }

    //初始化buffer
    for (i = 0; i < NBUF; i++){
        bufs[i].op = UNUSED;
        bufs[i].aiocb.aio_buf = bufs[i].data;
        bufs[i].aiocb.aio_sigevent.sigev_notify = SIGEV_NONE;
        aiolist[i] = NULL;
    }

    numop = 0;
    while (true){
        for (i = 0; i < NBUF; i++){
            switch (bufs[i].op) {
                case UNUSED:
                    //Read from input file if more data remains unread
                    if (off < statbuf.st_size){
                        bufs[i].op = READ_PENDING;
                        bufs[i].aiocb.aio_fildes = input_fd;
                        bufs[i].aiocb.aio_offset = off;
                        off += BSZ;
                        if (off >= statbuf.st_size){
                            bufs[i].last = 1;
                        }
                        bufs[i].aiocb.aio_nbytes = BSZ;
                        if (aio_read(&bufs[i].aiocb) < 0){
                            err_sys("aio_read failed");
                        }
                        aiolist[i] = &bufs[i].aiocb;
                        numop++;
                    }
                    break;
                case READ_PENDING:
                    if ((err = aio_error(&bufs[i].aiocb)) == EINPROGRESS){
                        continue;
                    }
                    if (err != 0){
                        if (err == -1){
                            err_sys("aio_error failed");
                        } else{
                            err_exit(err, "read failed");
                        }
                    }

                    //a read complete; translate the buffer and write it
                    if ((n = aio_return(&bufs[i].aiocb)) < 0){
                        err_sys("aio_return failed");
                    }
                    if (n != BSZ && !bufs[i].last){
                        err_quit("short read (%d/%d)", n, BSZ);
                    }
                    for (j = 0; j < n; j++){
                        bufs[i].data[i] = translate(bufs[i].data[j]);
                    }
                    bufs[i].op = WRITE_PENDING;
                    bufs[i].aiocb.aio_fildes = output_fd;
                    bufs[i].aiocb.aio_nbytes = n;
                    if (aio_write(&bufs[i].aiocb) < 0){
                        err_sys("aio_write failed");
                    }
                    //retain our spot in aiolist
                    break;
                case WRITE_PENDING:
                    if ((err = aio_error(&bufs[i].aiocb)) == EINPROGRESS){
                        continue;
                    }
                    if (err != 0){
                        if (err == -1){
                            err_sys("aio_error failed");
                        } else{
                            err_exit(err, "write failed");
                        }
                    }

                    // A write is complete; mark the buffer unused
                    if ((n = aio_return(&bufs[i].aiocb)) < 0){
                        err_sys("aio_return failed");
                    }
                    if (n != bufs[i].aiocb.aio_nbytes){
                        err_quit("short write (%d/%d)", n, BSZ);
                    }
                    aiolist[i] = NULL;
                    bufs[i].op = UNUSED;
                    numop--;
                    break;
            }
        }
        if (numop == 0){
            if (off >= statbuf.st_size){
                break;
            }
        } else{ //还有异步I/O操作未完成，阻塞进程，直到异步I/O操作完成
            if (aio_suspend(aiolist, NBUF, NULL) < 0){
                err_sys("aio_suspend failed");
            }
        }
    }

    bufs[0].aiocb.aio_fildes = output_fd;
    if (aio_fsync(O_SYNC, &bufs[0].aiocb) < 0){
        err_sys("aio_fsync failed");
    }

    exit(0);
}
































