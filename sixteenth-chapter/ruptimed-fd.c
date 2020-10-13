//
// Created by 王勇椿 on 2020/10/12.
//
//采用文件描述符来访问套接字的好处是允许程序对网络访问一无所知(对程序隐藏了网络访问的细节)
//例子:将uptime命令的标准输出和标准错误安排成为与客户端连接的套接字端点
#include "../include/apue.h"
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <stdbool.h>

#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

extern int initserver(int, const struct sockaddr *, socklen_t, int);
void serve(int);

void
serve(int sockfd){

    int clfd, status;
    pid_t pid;

    set_cloexec(sockfd);
    while (true){

        if ((clfd = accept(sockfd, NULL, NULL)) < 0){
            syslog(LOG_ERR, "ruptimed: accept error: %s", strerror(errno));
            exit(1);
        }

        if ((pid = fork()) < 0){
            syslog(LOG_ERR, "ruptimed: fork error: %s", strerror(errno));
            exit(1);
        } else if (pid == 0){
            /**
             * parent process called daemonize, so STDIN_FILENO, STDOUT_FILENO and STDERR_FILENO are
             * already open to /dev/null. Thus, the call to close doesn't need to be protected by checks
             * that clfd isn't already equal to one of these value
             */
             if (dup2(clfd, STDOUT_FILENO) != STDOUT_FILENO || dup2(clfd, STDERR_FILENO) != STDERR_FILENO){
                 syslog(LOG_ERR, "ruptimed: unexpected error");
                 exit(1);
             }
             close(clfd);
             execl("usr/bin/uptime", "uptime", (char *)0);
             syslog(LOG_ERR, "ruptimed: expected return from exec: %s", strerror(errno));
        } else{
            close(clfd);
            waitpid(pid, &status, 0);
        }
    }
}

int
main(int argc, char *argv[]){

    struct addrinfo *aiplist, *aip;
    struct addrinfo hint;
    int sockfd, err, n;
    char *host;

    if (argc != 1){
        err_quit("usage: ruptimed");
    }
    if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0){
        n = HOST_NAME_MAX;
    }
    if ((host = malloc(n)) == NULL){
        err_sys("malloc error");
    }
    if (gethostname(host, n) < 0){
        err_sys("gethostname error");
    }
    daemonize("ruptimed");
    memset(&hint, 0, sizeof(hint));
    hint.ai_flags = AI_CANONNAME;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;

    if ((err = getaddrinfo(host, "ruptime", &hint, &aiplist)) != 0){
        syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s", gai_strerror(err));
        exit(1);
    }
    for (aip = aiplist; aip != NULL; aip = aip->ai_next){
        if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr, aip->ai_addrlen, QLEN)) >= 0){
            serve(sockfd);
            exit(0);
        }
    }

    exit(1);
}















