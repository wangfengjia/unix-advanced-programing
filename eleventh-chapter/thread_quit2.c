//
// Created by 王勇椿 on 2020/9/5.
//
//pthread_create()和pthread_quit()函数的无类型指针参数可以传递的值不止一个，还可以传递结构的地址
//这时就需要注意，这个结构所使用的内存必须在调用者完成调用后必须有效，有两个在线程栈上为结构分配内存空间出现问题的例子
//1. 当这个结构所需的内存空间在线程的栈上分配的时候，然后把指向这个结构的指针传递给pthread_exit()函数，那么调用pthread_join的线程试图使用该结构时，
//   这个栈有可能被撤销，这块内存可能另作他用
//2. 在调用线程栈上分配该结构，那么其他线程在使用该结构时内容可能发生了改变
//解决这个问题的方法可以使用全局结构或者用malloc函数分配结构

#include <pthread.h>
#include "../include/apue.h"

struct foo{
    int a, b, c, d;
};

void printfoo(const char *, const struct foo *);
void *thr1_fun(void *args);
void *thr2_fun(void *args);

int main(void){

    int err;
    pthread_t td1, td2;
    struct foo *fp;

    err = pthread_create(&td1, NULL, thr1_fun, NULL);
    if (err != 0){
        err_exit(err, "can't create thread 1");
    }
    err = pthread_join(td1, (void *)&fp);
    if (err != 0){
        err_exit(err, "can't join with thread 1");
    }
    sleep(1);
    printf("parent starting second thread\n");
    err = pthread_create(&td2, NULL, thr2_fun, NULL);
    if (err != 0){
        err_exit(err, "can't create thread 2");
    }
    sleep(1);
    printfoo("parent:\n", fp);
    exit(0);
}

void printfoo(const char *str, const struct foo *foo){

    printf("%s", str);
    printf(" structure at 0x%lx\n", (unsigned long)foo);
    printf(" foo.a = %d\n", foo->a);
    printf(" foo.b = %d\n", foo->b);
    printf(" foo.c = %d\n", foo->c);
    printf(" foo.d = %d\n", foo->d);
}

void *thr1_fun(void *args){

    struct foo foo = {1, 2, 3, 4};
    printfoo("thread 1:\n", &foo);
    pthread_exit((void *)&foo);
}

void *thr2_fun(void *args){
    printf("thread 2:ID is %lu\n", (unsigned long)pthread_self());
    pthread_exit((void *)0);
}

