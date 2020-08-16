//
// Created by 王勇椿 on 2020/8/16.
//

//进程资源限制，一般是在系统初始化时由0号进程建立的，然后由后续进程继承，可以进行修改

#include <sys/resource.h>
#include "../include/apue.h"

#define doit(name) pr_limits(#name, name)

static void pr_limits(char *, int);


int main(void){
#ifdef RLIMIT_AS
    doit(RLIMIT_AS);
#endif
    doit(RLIMIT_CORE);
    doit(RLIMIT_CPU);
    doit(RLIMIT_DATA);
    doit(RLIMIT_FSIZE);

#ifdef RLIMIT_MEMLOCK
    doit(RLIMIT_MEMLOCK);
#endif

#ifdef RLIMIT_MSGQUEUE
    doit(RLIMIT_MSGQUEUE);
#endif

#ifdef RLIMIT_NICE
    doit(RLIMIT_NICE);
#endif
    doit(RLIMIT_NOFILE);
#ifdef RLIMIT_NPROC
    doit(RLIMIT_NPROC);
#endif

#ifdef RLIMIT_NPTS
    doit(RLIMIT_NPTS);
#endif

#ifdef RLIMIT_RSS
    doit(RLIMIT_RSS);
#endif

#ifdef RLIMIT_SBSIZE
    doit(RLIMIT_SBSIZE);
#endif

#ifdef RLIMIT_SIGPENDING
    doit(RLIMIT_SIGPENDING);
#endif

    doit(RLIMIT_STACK);
#ifdef RLIMIT_SWAP
    doit(RLIMIT_STACK);
#endif
#ifdef RLIMIT_VMEM
    doit(RLIMIT_VMEM);
#endif

    exit(0);
}


static void pr_limits(char *name, int resource){


    struct rlimit limit;
    unsigned long long lim;

    if (getrlimit(resource, &limit) < 0){
        err_sys("getrlimit error for %s", name);
    }
    printf("%-14s ", name);
    if (limit.rlim_cur == RLIM_INFINITY){
        printf("(infinite) ");
    } else{
        lim = limit.rlim_cur;
        printf("%10lld ", lim);
    }

    if (limit.rlim_max == RLIM_INFINITY){
        printf("(infinite) ");
    } else{
        lim = limit.rlim_max;
        printf("%10lld", lim);
    }

    putchar((int)'\n');
}