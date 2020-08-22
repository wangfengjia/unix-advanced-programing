//
// Created by 王勇椿 on 2020/8/22.
//
//进程时间

#include "../include/apue.h"
#include "../include/my_apue.h"
#include <sys/times.h>

static void print_times(clock_t, struct tms *, struct tms *);
static void do_cmd(char *);

int main(int argc, char *argv[]){

    int i;

    setbuf(stdout, NULL);
    for (i = 1; i < argc; i++){
        do_cmd(argv[i]);
    }

    exit(0);
}

static void do_cmd(char *cmd){

    struct tms tmsstart, tmsend;
    clock_t start, end;
    int status;

    //start value
    if ((start = times(&tmsstart)) == -1){
        err_sys("times error");
    }
    //execute command
    if ((status = system(cmd)) < 0){
        err_sys("system() error");
    }

    //ending value
    if ((end = times(&tmsend)) == -1){
        err_sys("times error");
    }

    print_times(end - start, &tmsstart, &tmsend);
    print_exit(status);
}

static void print_times(clock_t real, struct tms *tmsstart, struct tms *tmsend){

    static long clktck = 0;
    if (clktck == 0){
        if ((clktck = sysconf(_SC_CLK_TCK)) < 0){
            err_sys("sysconf error");
        }
    }

    printf(" read: %7.2f\n", real / (double) clktck);
    printf(" user: %7.2f\n", (tmsend->tms_utime - tmsstart->tms_utime) / (double) clktck);
    printf(" sys: %7.2f\n", (tmsend->tms_stime - tmsstart->tms_stime) / (double) clktck);
    printf(" child user: %7.2f\n", (tmsend->tms_cutime - tmsstart->tms_cutime) / (double) clktck);
    printf(" child sys: %7.2f\n", (tmsend->tms_cstime - tmsstart->tms_cstime) / (double) clktck);
}

