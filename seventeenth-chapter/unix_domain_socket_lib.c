//
// Created by 王勇椿 on 2020/10/14.
//
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <time.h>
#include "unix_domain_socket_lib.h"

#define QLEN 10

#define STALE 30 //client's name can't be older than this(sec)
#define CLIENT_PATH "/var/temp/"
#define CLIENT_PERM S_IRWXU


int
server_listen(const char *name){

    int fd, len, err;
    int rval = 0;
    struct sockaddr_un un;
    if (strlen(name) >= sizeof(un.sun_path)){
        errno = ENAMETOOLONG;
        return (-1);
    }

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){
        return (-2);
    }

    //in case it already exists
    unlink(name);

    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, name);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(name);

    if (bind(fd, (struct sockaddr *)&un, len) < 0){
        rval = -3;
        goto errout;
    }

    //tell kernel we are a server,服务器进程调用listen函数来表示它要在在fd所指示的地址上监听客户进程的连接请求
    if (listen(fd, QLEN) < 0){
        rval = -4;
        goto errout;
    }

    errout:
        //这条语句的目的是以防执行close函数时出错，errno变量的值被重置为上面执行过程中赋值给error变量的值
        err = errno;
        close(fd);
        errno = err;
        return (rval);
}

/**
 * wait for a client connection request to arrive, anc accept it
 * we also obtain the client's user ID from the pathname that is must bind before calling us
 * return new fd if all ok, <0 on error
 * @param listenfd
 * @param uidptr
 * @return
 */
int
server_accept(int listenfd, uid_t *uidptr){

    int clifd, err;
    int rval = 0;
    socklen_t len;
    time_t staletime;
    struct sockaddr_un un;
    struct stat statbuf;
    char *name;

    if ((name = malloc(sizeof(un.sun_path) + 1)) == NULL){
        return (-1);
    }
    len = sizeof(un);
    if ((clifd = accept(listenfd, (struct sockaddr *)&un, &len)) < 0){
        free(name);
        return (-2);
    }

    //obtain the client's uid from its calling address
    len -= offsetof(struct sockaddr_un, sun_path);
    memcpy(name, un.sun_path, len);
    name[len] = 0; // null terminate
    if (stat(name, &statbuf) < 0){
        rval = -3;
        goto errout;
    }
#ifndef S_ISSOCK
    if(S_ISSOCK(statbuf.st_mode) == 0){
        rval = -4;
        goto errout;
    }
#endif

    if ((statbuf.st_mode & (S_IRWXG | S_IRWXO)) || ((statbuf.st_mode & S_IRWXU) != S_IRWXU)){
        rval = -5; //
        goto errout;
    }
    staletime = time(NULL) - STALE;
    if (statbuf.st_atime < staletime || statbuf.st_ctime < staletime || statbuf.st_mtime < staletime){
        rval = -6; //i-node is too old
        goto errout;
    }

    if (uidptr != NULL){
        *uidptr = statbuf.st_uid; //return uid of caller
    }
    unlink(name);
    free(name);
    return clifd;

    errout:
        err = errno;
        close(clifd);
        free(name);
        errno = err;
        return (rval);
}

int
client_connect(const char *name){

    int fd, len, err;
    int rval = 0;
    struct sockaddr_un un,sun;
    int do_unlink = 0;

    if (strlen(name) >= sizeof(un.sun_path)){
        errno = ENAMETOOLONG;
        return (-1);
    }

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){
        return (-1);
    }

    //client socket bind address
    //客户进程套接字没让系统选择默认地址的原因是:系统选择默认地址，服务器进程将不能区分各个客户进程
    // (如果不为unix域套接字显式地绑定名字，内核会代表我们隐式地绑定一个地址且不在文件系统创建文件来表示这个套接字)
    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    sprintf(un.sun_path, "%s%05ld", CLIENT_PATH, (long)getpid());
    len = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);

    unlink(un.sun_path); //in case address already exists
    if (bind(fd, (struct sockaddr *)&un, len) < 0){
        rval = -2;
        goto errout;
    }
    if (chmod(un.sun_path, CLIENT_PERM) < 0){
        rval = -3;
        do_unlink = 1;
        goto errout;
    }

    //fill socket address structure with server's address
    memset(&sun, 0, sizeof(sun));
    sun.sun_family = AF_UNIX;
    strcpy(sun.sun_path, name);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(name);
    if (connect(fd, (struct sockaddr *)&un, len) < 0){
        rval = -4;
        do_unlink = 1;
        goto errout;
    }

    return (fd);

    errout:
        err = errno;
        close(fd);
        if (do_unlink){
            unlink(un.sun_path);
        }
        errno = err;
        return (rval);
}






























