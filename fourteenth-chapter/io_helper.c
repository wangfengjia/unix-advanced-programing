//
// Created by 王勇椿 on 2020/9/23.
//
#include "io_helper.h"

ssize_t my_readn(int fd, void *ptr, size_t n){

    size_t nleft;
    ssize_t nread;

    nleft = n;
    while (nleft > 0){
        if ((nread = read(fd, ptr, nleft)) < 0){
            if (nleft == n){//第一次读的时候出错
                return (-1);
            } else{ //若是已经读了一些数据之后出错，则返回的是已传输数据量，而非错误
                break;
            }
        } else if (nread == 0){//已达到文件末尾，而且在此之前已经成功地读了一些数据，但尚未满足所要求的量，则返回已复制到调用者缓冲区中的字节数
            break; //文件末尾
        }
        nleft -= nread;
        ptr += nread;
    }

    return (n - nleft); //return n >= 0
}

ssize_t my_writen(int fd, const void *ptr, size_t n){

    size_t nleft;
    ssize_t nwritten;

    nleft = n;
    while (nleft > 0){
        if ((nwritten = write(fd, ptr, nleft)) < 0){
            if (nleft == n){
                return (-1);
            } else{
                break;
            }
        } else if (nwritten == 0){
            break;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }

    return (n - nleft);
}

