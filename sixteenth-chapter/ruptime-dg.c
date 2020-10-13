//
// Created by 王勇椿 on 2020/10/13.
//
//无连接的套接字客户端，采用数据报套接字接口
#include "../include/apue.h"
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>

#define BUFLEN 128
#define TIMEOUT 20

void sigalrm(int);
void print_time(int, struct addrinfo *);

void
sigalrm(int signo){

}

void
print_time(int sockfd, struct addrinfo *addr){

    int n;
    char buf[BUFLEN];

    buf[0] = 0;
    if (sendto(sockfd, buf, 1, 0, addr->ai_addr, addr->ai_addrlen) < 0){
        err_sys("sendto error");
    }
    alarm(TIMEOUT);
    if ((n = recvfrom(sockfd, buf, BUFLEN, 0, NULL, NULL)) < 0){
        if (errno != EINTR){
            alarm(0);
        }
        err_sys("recv error");
    }
    alarm(0);
    write(STDOUT_FILENO, buf, n);
}

int
main(int argc, char *argv[]){

    struct addrinfo *aiplist, *aip;
    struct addrinfo hint;
    int sockfd, err;
    struct sigaction sa;

    if (argc != 2){
        err_quit("usage: ruptime hostname");
    }
    sa.sa_handler = sigalrm;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGALRM, &sa, NULL) < 0){
        err_sys("sigaction error");
    }

    memset(&hint, 0, sizeof(hint));
    hint.ai_socktype = SOCK_DGRAM;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    if ((err = getaddrinfo(argv[1], "ruptime", &hint, &aiplist)) != 0){
        err_quit("getaddrinfo error: %s", gai_strerror(err));
    }

    for (aip = aiplist; aip != NULL; aip = aip->ai_next){
        if ((sockfd = socket(aip->ai_family, SOCK_DGRAM, 0)) < 0){
            err = errno;
        } else{
            print_time(sockfd, aip);
            exit(0);
        }
    }

    fprintf(stderr, "can't contact %s: %s\n", argv[1], strerror(err));
    exit(1);
}

























