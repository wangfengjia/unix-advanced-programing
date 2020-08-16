//
// Created by 王勇椿 on 2020/8/16.
//

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){

    time_t t;
    struct tm *tmp;
    char buf1[16];
    char buf2[64];

    time(&t);
    tmp = localtime(&t);

    if (strftime(buf1, 16, "time and date: %F %X", tmp) == 0){
        printf("buffer length 16 is too small\n");
    } else{
        printf("%s\n", buf1);
    }

    if (strftime(buf2, 64, "time and date: %F %X", tmp) == 0){
        printf("buffer length 64 is too small\n");
    } else{
        printf("%s\n", buf2);
    }
}



