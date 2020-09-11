//
// Created by 王勇椿 on 2020/9/10.
//

#ifndef UNIX_ADVANCED_PROGRAMING_THREAD_SAFE_H
#define UNIX_ADVANCED_PROGRAMING_THREAD_SAFE_H

static void thread_init(void);
//一般以"_r"结尾的函数是线程安全的
int getenv_r(const char *, char *, int buflen);
#endif //UNIX_ADVANCED_PROGRAMING_THREAD_SAFE_H
