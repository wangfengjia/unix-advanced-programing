//
// Created by 王勇椿 on 2020/9/1.
//

#ifndef UNIX_ADVANCED_PROGRAMING_MYSIGNAL_H
#define UNIX_ADVANCED_PROGRAMING_MYSIGNAL_H

#include "../include/apue.h"

Sigfunc *mysignal(int, Sigfunc *);
//signal函数的第二个版本，它力图阻止被中断的系统调用重启动
Sigfunc *mysignal_v2(int, Sigfunc *);
#endif //UNIX_ADVANCED_PROGRAMING_MYSIGNAL_H
