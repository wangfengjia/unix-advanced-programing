//
// Created by 王勇椿 on 2020/8/21.
//

//父子进程以不同的nice值运行，运行10s后，两个进程都打印各自的计数值并终止。
//通过比较不同的nice值的进程的计数值的差异，可以知道nice值如何影响进程调度

#include "../include/apue.h"
#include <errno.h>
#include <sys/time.h>
#include <stdbool.h>
#include <sys/syslimits.h>

#if defined(MACOS)
#elif defined(SOLARIS)
#include <limits.h>
#elif defined(BSD)
#include <sys/param.h>
#endif

unsigned long long count;
struct timeval end;

void checktime(char *);

int main(int argc, char *argv[]){


    pid_t pid;
    char *str;
    int nzero;
    int ret;
    int adj = 0;

    //设置标准输出无缓冲
    setbuf(stdout, NULL);
#if defined(NZERO)
    nzero = NZERO;
#elif defined(_SC_NZERO)
    nzero = sysconf(_SC_NZERO);
#else
#error NZERO undefined
#endif

    printf("NZERO = %d\n", nzero);
    if (argc == 2){
        adj = strtol(argv[1], NULL, 10);
    }
    gettimeofday(&end, NULL);
    end.tv_sec += 3; //run for 10 seconds

    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid == 0){
        str = "child";
        printf("current nice value in child is %d, adjusting by %d\n", nice(0) + nzero, adj);
        errno = 0;
        if ((ret = nice(adj)) == -1 && errno != 0){
            err_sys("child set scheduling priority");
        }
        printf("now child nice value is %d\n", ret + nzero);
    } else{
        str = "parent";
        printf("current nice value in parent is %d\n", nice(0) + nzero);
    }

    while (true){
        if (++count == 0){
            err_quit("%s counter wrap", str);
        }
        checktime(str);
    }
}


void checktime(char *str){

    struct timeval tv;
    gettimeofday(&tv, NULL);
    if (tv.tv_sec >= end.tv_sec && tv.tv_usec >= end.tv_usec){
        printf("%s count = %lld\n", str, count);
        exit(0);
    }
}