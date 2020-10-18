//
// Created by 王勇椿 on 2020/10/18.
//
#include "opend_v2.h"
#include <syslog.h>

int debug;
int oflag_v2;
int client_size;
int log_to_stderr;

char errmsg_v2[MAXLINE];
char *pathname_v2;
Client *client = NULL;

int
main(int argc, char *argv[]){

    int c;

    log_open("open.serv", LOG_PID, LOG_USER);

    opterr = 0; //don't want getopt() writing to stderr
    while ((c = getopt(argc, argv, "d")) != EOF){
        switch (c) {
            //debug模式
            case 'd':
                debug = log_to_stderr = 1;
                break;
            case '?':
                err_quit("unrecognized option: -%c", optopt);
        }
    }
    if (debug == 0){
        daemonize("opend_test_v2");
    }

    loop(); // never returns
}