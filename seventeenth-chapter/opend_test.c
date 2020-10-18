//
// Created by 王勇椿 on 2020/10/17.
//
#include "opend.h"
#include <stdbool.h>
#include <syslog.h>

char errmsg[MAXLINE];
int oflag;
char *pathname;


int
main(void){

    int nread;
    char buf[MAXLINE];

    while (true){ //read arg buffer from client, process request

        if ((nread = read(STDIN_FILENO, buf, MAXLINE)) < 0){
            err_sys("read error on stream pipe");
        } else if (nread == 0){
            break;
        }

        handle_request(buf, nread, STDOUT_FILENO);
    }

    exit(0);
}

