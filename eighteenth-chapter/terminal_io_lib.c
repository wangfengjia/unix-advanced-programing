//
// Created by 王勇椿 on 2020/10/21.
//
#include "terminal_io_lib.h"
#include <termios.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <signal.h>
#include <stdio.h>

struct devdir{
    struct devdir *d_next;
    char *d_name;
};

static struct devdir *head;
static struct devdir *tail;
static char pathname[_POSIX_NAME_MAX + 1];

static void add(char *);
static void cleanup(void);
static char *searchdir(char *, struct stat *);

static void
add(char *dirname){

    struct devdir *ddp;
    int len;

    len = strlen(dirname);
    //skip ., .., and /dev/fd
    if ((dirname[len - 1] == '.') || (dirname[len - 2] == '/' || (dirname[len - 2] == '.' && dirname[len - 3] == '/'))){
        return;
    }
    if (strcmp(dirname, "/dev/fd") == 0){
        return;
    }
    if ((ddp = malloc(sizeof(struct devdir))) == NULL){
        return;
    }
    if ((ddp->d_name = strdup(dirname)) == NULL){
        free(ddp);
        return;
    }

    ddp->d_next = NULL;
    if (tail == NULL){
        head = ddp;
        tail = ddp;
    } else{
        tail->d_next = ddp;
        tail = ddp;
    }
}

static void
cleanup(void){

    struct devdir *ddp, *nddp;

    ddp = head;
    while (ddp != NULL){
        nddp = ddp->d_next;
        free(ddp->d_name);
        free(ddp);
        ddp = nddp;
    }

    head = NULL;
    tail = NULL;
}

static char
*searchdir(char *dirname, struct stat *fdstatp){

    struct stat devstat;
    DIR *dp;
    int devlen;
    struct dirent *dirp;

    strcpy(pathname, dirname);
    if ((dp = opendir(pathname)) == NULL){
        return (NULL);
    }
    strcat(pathname, "/");
    devlen = strlen(pathname);
    while ((dirp = readdir(dp)) != NULL){
        strncpy(pathname + devlen, dirp->d_name, _POSIX_NAME_MAX - devlen);
        //skip aliases
        if (strcmp(pathname, "/dev/stdin") == 0 || strcmp(pathname, "/dev/stdout") == 0 || strcmp(pathname, "/dev/stderr") == 0){
            continue;
        }
        if (stat(pathname, &devstat) < 0){
            continue;
        }
        if (S_ISDIR(devstat.st_mode)){
            add(pathname);
            continue;
        }
        if (devstat.st_ino == fdstatp->st_ino && devstat.st_dev == fdstatp->st_dev){ //found a match
            closedir(dp);
            return (pathname);
        }
    }

    closedir(dp);
    return (NULL);
}

char
*my_ttyname(int fd){

    struct stat fdstat;
    struct devdir *ddp;
    char *rval;

    if (isatty(fd) == 0){
        return NULL;
    }
    if (fstat(fd, &fdstat) < 0){
        return (NULL);
    }
    if (S_ISCHR(fdstat.st_mode) == 0){
        return (NULL);
    }

    rval = searchdir("/dev", &fdstat);
    if (rval == NULL){
        for (ddp = head; ddp != NULL; ddp = ddp->d_next){
            if ((rval = searchdir(ddp->d_name, &fdstat)) != NULL){
                break;
            }
        }
    }

    cleanup();
    return (rval);
}

int my_isatty(int fd){

    struct termios ts;
    return (tcgetattr(fd, &ts) != -1);
}

char
*getpass(const char *prompt){

    static char buf[MAX_PASS_LEN + 1]; //null byte end
    char *ptr;
    sigset_t sig, osig;
    struct termios ts,ots;
    FILE *fp;
    int c;

    if ((fp = fopen(ctermid(NULL), "r+")) == NULL){
        return (NULL);
    }
    setbuf(fp, NULL);

    sigemptyset(&sig);
    sigaddset(&sig, SIGINT); //block SIGINT
    sigaddset(&sig, SIGTSTP); // block SIGTSTP
    sigprocmask(SIG_BLOCK, &sig, &osig); //save mask

    tcgetattr(fileno(fp), &ts); // save tty state
    ots = ts; //structure copy
    ts.c_cflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
    tcsetattr(fileno(fp), TCSAFLUSH, &ts);
    fputs(prompt, fp);

    ptr = buf;
    while ((c = getc(fp)) != EOF && c != '\n'){
        if (ptr < &buf[MAX_PASS_LEN]){
            *ptr++ = c;
        }
    }
    *ptr = 0; //null terminate
    putc('\n', fp); //echo a newline

    tcsetattr(fileno(fp), TCSAFLUSH, &ots); // restore TTY state
    sigprocmask(SIG_SETMASK, &osig, NULL); //restore mask
    fclose(fp);
    return (buf);
}


