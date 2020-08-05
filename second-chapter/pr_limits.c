//
// Created by 王勇椿 on 2020/8/4.
//


#include "../include/apue.h"
#include <errno.h>
#include <limits.h>

static void pr_sysconf(char *, int);
static void pr_pathconf(char *, char *, int);

int main(int argc, char *argv[]){

    if (argc != 2){
        err_quit("usage: a.out <dirname>");
    }
    printf("dir name: %s\n", argv[1]);
#ifdef ARG_MAX
    printf("ARG_MAX defined to be %ld\n", (long)ARG_MAX + 0);
#else
    printf("no symbol for ARG_MAX\n");
#endif

#ifdef _SC_ARG_MAX
    pr_sysconf("ARG_MAX = ", _SC_ARG_MAX);
#else
    printf("no symbol for _SC_ARG_MAX\n");
#endif

#ifdef MAX_CANON
    printf("MAX_CANON defined to be %ld\n", (long)MAX_CANON + 0);
#else
    printf("no symbol for MAX_CANON\n");
#endif

#ifdef _PC_MAX_CANON
    pr_pathconf("MAX_CANNON = ", argv[1], _PC_MAX_CANON);
#else
    printf("no symbol for _PC_MAX_CANON\n");
#endif
}
static void pr_sysconf(char *message, int name){

    long value;
    fputs(message, stdout);

    errno = 0;
    if ((value = sysconf(name)) < 0){

        if (errno != 0){
            if (errno == EINVAL){
                fputs(" (not supported)\n", stdout);
            } else{
                err_sys("sysconf error");
            }
        } else{
            fputs(" (no limits)\n", stdout);
        }
    } else{
        printf(" %ld\n", value);
    }
}

static void pr_pathconf(char *message, char *path, int name){

    long val;
    fputs(message, stdout);

    errno = 0;
    if ((val = pathconf(path, name)) < 0){

        if (errno != 0){
            if (errno == EINVAL){
                fputs(" (not supported)\n", stdout);
            } else{
                err_sys("pathconf error, path=%s\n", path);
            }
        } else{
            fputs(" (no limit)\n", stdout);
        }
    } else{
        printf(" %ld\n", val);
    }
}
