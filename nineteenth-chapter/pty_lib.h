//
// Created by 王勇椿 on 2020/10/22.
//

#ifndef UNIX_ADVANCED_PROGRAMING_PTY_LIB_H
#define UNIX_ADVANCED_PROGRAMING_PTY_LIB_H

/**
 * 1. 一个进程调用ptym_open来打开一个主设备并且得到从设备名，这个进程然后fork子进程，子进程再调用setsid建立新的会话后调用ptys_open打开从设备，这就是
 *    从设备如何成为子进程控制终端的过程
 */
#include <termios.h>

int my_ptym_open(char *pts_name, int pts_namesz);
int my_ptys_open(char *pts_name);
int my_pty_fork(int *, char *, int, const struct termios *, const struct winsize *);

#endif //UNIX_ADVANCED_PROGRAMING_PTY_LIB_H
