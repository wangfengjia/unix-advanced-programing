//
// Created by 王勇椿 on 2020/8/16.
//
//时间

#include <time.h>
#include <unistd.h>
#include "../include/apue.h"

int main(void){

    time_t calptr;
    if (time(&calptr) < 0){
        err_sys("time error");
    }

    struct tm *now = localtime(&calptr);
    printf("%d-%d-%d %d:%d:%d", 1900+ now->tm_year, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);


}
