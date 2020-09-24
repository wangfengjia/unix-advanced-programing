//
// Created by 王勇椿 on 2020/9/23.
//

#ifndef UNIX_ADVANCED_PROGRAMING_IO_HELPER_H
#define UNIX_ADVANCED_PROGRAMING_IO_HELPER_H

/**
 * 对于像管道、FIFO、终端设备和网络设置有下面两种性质
 * 1.一次read操作返回的数据可能少于要求的数据(即使还没达到文件末端也是这样)
 * 2.一次write操作的返回值可能少于所指定的字节数(例如:内核输出缓冲区满了)
 * 解决办法:下面封装的两个方法就为了解决这种情况:指定要读或者写的字节数，返回值小于要求的字节数时，按需多次调用read和write
 */
#include "../include/apue.h"

ssize_t my_readn(int, void *, size_t);
ssize_t my_writen(int, const void *, size_t);
#endif //UNIX_ADVANCED_PROGRAMING_IO_HELPER_H
