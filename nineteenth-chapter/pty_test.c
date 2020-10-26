//
// Created by 王勇椿 on 2020/10/26.
//
//pty程序:当用pty执行另一个程序时，程序就会在一个它自己的会话中执行，并与一个伪终端连接
#include "../include/apue.h"
#include "pty_lib.h"
#include "driver.h"
#include "loop.h"
#include <termios.h>

#ifdef LINUX
#define OPTSTR "+d:einv" //第一个字符设置为加号的原因是在linux中强制POSIX行为
#else
#define OPTSTR "d:einv"
#endif

static void set_noecho(int);


int main(int argc, char *argv[]){

    int fdm, c, ignoreeof, interactive, noecho, verbose;
    pid_t pid;
    char *driver;
    char slave_name[20];
    struct termios orig_termios;
    struct winsize size;

    interactive = isatty(STDIN_FILENO);
    ignoreeof = 0;
    noecho = 0;
    verbose = 0;
    driver = NULL;

    opterr = 0; // don't want getopt() writing to stderr
    while ((c = getopt(argc, argv, OPTSTR)) != EOF){

        switch (c) {
            //driver for stdin/stdout
            case 'd':
                driver = optarg;
                break;
            //noecho for slave pty's line discipline
            case 'e':
                noecho = 1;
                break;
            //ignore EOF on standard input
            case 'i':
                ignoreeof = 1;
                break;
            //no interactive
            case 'n':
                interactive = 0;
                break;
            //verbose
            case 'v':
                verbose = 1;
                break;
            case '?':
                err_quit("unrecognized option: -%c", optopt);
        }
    }

    if (optind >= argc){
        err_quit("usage: pty [ -d driver -einv ] program [ arg ...]");
    }
    if (interactive){ //fetch current termios and window size
        if (tcgetattr(STDIN_FILENO, &orig_termios) < 0){
            err_sys("tcgetattr error on stdin");
        }
        if (ioctl(STDIN_FILENO, TIOCSWINSZ, (char *) &size) < 0){
            err_sys("TIOCSWINSZ error");
        }
        pid = my_pty_fork(&fdm, slave_name, sizeof(slave_name), &orig_termios, &size);
    } else{
        pid = my_pty_fork(&fdm, slave_name, sizeof(slave_name), NULL, NULL);
    }

    if (pid < 0){
        err_sys("fork error");
    } else if (pid == 0){
        if (noecho){
            set_noecho(STDIN_FILENO); //stdin is slave pty
        }
        if (execvp(argv[optind], &argv[optind]) < 0){
            err_sys("can't execute: %s", argv[optind]);
        }
    }

    if (verbose){
        fprintf(stderr, "slave name = %s\n", slave_name);
        if (driver != NULL){
            fprintf(stderr, "driver = %s\n", driver);
        }
    }

    if (interactive && driver == NULL){
        if (tty_raw(STDIN_FILENO) < 0){ //user's tty to raw mode
            err_sys("tty_raw error");
        }
        if (atexit(tty_atexit) < 0){ // reset user's tty on exit
            err_sys("atexit error");
        }
    }
    if (driver){
        do_driver(driver); // changes our stdin/stdout
    }

    loop(fdm, ignoreeof); // copy stdin -> ptym, ptym->stdout
    exit(0);
}

//Turn off cho (for slave pty)
static void set_noecho(int fd){

    struct termios termios;

    if (tcgetattr(fd, &termios) < 0){
        err_sys("tcgetattr error");
    }
    termios.c_cflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
    //Also Turn off NL to CR/NL mapping the output
    termios.c_oflag &= ~(ONLCR);
    if (tcsetattr(fd, TCSANOW, &termios) < 0){
        err_sys("tcsetattr error");
    }
}



