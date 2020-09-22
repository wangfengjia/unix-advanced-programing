//
// Created by 王勇椿 on 2020/9/18.
//

#ifndef UNIX_ADVANCED_PROGRAMING_LOCK_H
#define UNIX_ADVANCED_PROGRAMING_LOCK_H
#include <fcntl.h>
//为了避免每次分配flock结构，然后又填入各项信息，所以把这些信息封装到lock_reg函数做处理
int lock_reg(int, int, int, off_t, int, off_t);
pid_t lock_test(int, int, off_t, int, off_t);
#endif //UNIX_ADVANCED_PROGRAMING_LOCK_H
