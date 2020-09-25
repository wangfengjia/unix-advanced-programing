//
// Created by 王勇椿 on 2020/9/24.
//

#ifndef UNIX_ADVANCED_PROGRAMING_POPEN_IMPLEMENT_H
#define UNIX_ADVANCED_PROGRAMING_POPEN_IMPLEMENT_H

//popen和pclose的实现
#include "../include/apue.h"

FILE *my_popen(const char *, const char *);
int my_pclose(FILE *);

#endif //UNIX_ADVANCED_PROGRAMING_POPEN_IMPLEMENT_H
