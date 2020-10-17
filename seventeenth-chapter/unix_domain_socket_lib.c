//
// Created by 王勇椿 on 2020/10/14.
//
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <time.h>
#include <stdbool.h>
#include "unix_domain_socket_lib.h"

#define QLEN 10

#define STALE 30 //client's name can't be older than this(sec)
#define CLIENT_PATH "/var/temp/"
#define CLIENT_PERM S_IRWXU

//一个进程向另外一个进程传送一个打开文件描述符相关的宏和全局变量
//size of control buffer to send/recv one file descriptor
#define CONTROLEN CMSG_LEN(sizeof(int))
static struct cmsghdr *cmptr = NULL; //malloc'ed first time

//send_fd_v2方法相关的宏
#if defined(SCM_CREDS) // BSD interface
#define CREDSTRUCT cmsgcred
#define CR_UID cmcred_id
#define SCM_CREDTYPE SCM_CREDS
#elif defined(SCM_CREDENTIALS)  //linux interface
#define CREDSTRUCT ucred
#define SCM_CREDTYPE SCM_CREDENTIALS
#define CR_UID uid
#define CREDOPT SO_PASSCRED
#else
#error passing credentials is unsupported!
#endif

//size of control buffer to send/recv one file descriptor
#define RIGHTSLEN CMSG_LEN(sizeof(int))
#define CREDSLEN CMSG_LEN(sizeof(struct CREDSTRUCT))
#define CONTROLLEN_V2 (RIGHTSLEN + CREDSLEN)


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


int
my_send_fd(int fd, int fd_to_send){

    struct iovec iov[1];
    struct msghdr msg;
    char buf[2]; //send_fd()/recv_fd() 2-byte protocol

    iov[0].iov_base = buf;
    iov[0].iov_len = 2;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;

    if (fd_to_send < 0){
        msg.msg_control = NULL;
        msg.msg_controllen = 0;
        buf[1] = -fd_to_send; //nonzero status means error
        if (buf[1] == 0){
            buf[1] = 1; //-256, etc . would screw up protocol
        }
    } else{

        if (cmptr == NULL && (cmptr = malloc(CONTROLEN)) == NULL){
            return (-1);
        }
        cmptr->cmsg_level = SOL_SOCKET;
        cmptr->cmsg_type = SCM_RIGHTS;
        cmptr->cmsg_len = CONTROLEN;
        msg.msg_control = cmptr;
        msg.msg_controllen = CONTROLEN;
        *(int *)CMSG_DATA(cmptr) = fd_to_send; // the fd to pass

        buf[1] = 0; // zero status means ok
    }

    buf[0] = 0; //null byte flag to recv_fd()
    if (sendmsg(fd, &msg, 0) < 0){
        return (-1);
    }

    return 0;
}

int
my_send_err(int fd, int errorcode, const char *errmsg){

    int n;

    if ((n = strlen(errmsg)) > 0){
        if (write(fd, errmsg, n) != n){
            return (-1);
        }
    }

    if (errorcode >= 0){
        errorcode = -1; //必须是负数
    }

    if (send_fd(fd, errorcode) < 0){
        return -1;
    }

    return (0);
}

int
my_recv_fd(int fd, ssize_t (*userfunc)(int, const void *, size_t)){

    int newfd, nr, status;
    char *ptr;
    char buf[MAXLINE];
    struct iovec iov[1];
    struct msghdr msg;

    status = -1;
    while (true){

        iov[0].iov_base = buf;
        iov[0].iov_len = sizeof(buf);
        msg.msg_iov = iov;
        msg.msg_iovlen = 1;
        msg.msg_name = NULL;
        msg.msg_namelen = 0;
        if (cmptr == NULL && (cmptr = malloc(CONTROLEN)) == NULL){
            return (-1);
        }
        msg.msg_control = cmptr;
        msg.msg_controllen = CONTROLEN;
        if ((nr = recvmsg(fd, &msg, 0)) < 0){
            err_ret("recvmsg error");
        } else if (nr == 0){
            err_ret("connection closed by server");
            return (-1);
        }

        /**
        * see if this is final data with null & status, Null is next to last byte of buffer;
        * status byte is last byte.zero status means there is a file descriptor to receive
        */
        for (ptr = buf; ptr < &buf[nr];){
            if (*ptr++ == 0){
                if (ptr != &buf[nr - 1]){
                    err_dump("message format error");
                }
                status = *ptr & 0xFF; // prevent sign extension
                if (status == 0){
                    if (msg.msg_controllen < CONTROLEN){
                        err_dump("status = 0 but no fd");
                    }
                    newfd = *(int *)CMSG_DATA(cmptr);
                } else{
                    newfd -= status;
                }
                nr -= 2;
            }
        }

        if (nr > 0 && (*userfunc)(STDERR_FILENO, buf, nr) != nr){
            return (-1);
        }
        if (status >= 0){ // final data has arrived
            return (newfd); //descriptor, or -status
        }
    }
}

int
my_send_fd_v2(int fd, int fd_to_send){

    struct CREDSTRUCT *credp;
    struct cmsghdr *cmp;
    struct iovec iov[1];
    struct msghdr msg;
    char buf[2];

    iov[0].iov_base = buf;
    iov[0].iov_len = 2;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_flags = 0;
    if (fd_to_send < 0){
        msg.msg_control = NULL;
        msg.msg_controllen = 0;
        buf[1] = -fd_to_send;
        if (buf[1] == 0){
            buf[1] = 1;
        }
    } else{
        if (cmptr == NULL && (cmptr = malloc(CONTROLLEN_V2)) == NULL){
            return (-1);
        }

        msg.msg_control = cmptr;
        msg.msg_controllen = CONTROLLEN_V2;
        cmp = cmptr;
        cmp->cmsg_level = SOL_SOCKET;
        cmp->cmsg_type = SCM_RIGHTS;
        cmp->cmsg_len = RIGHTSLEN;
        *(int *)CMSG_DATA(cmp) = fd_to_send;
        cmp = CMSG_NXTHDR(&msg, cmp);
        cmp->cmsg_level = SOL_SOCKET;
        cmp->cmsg_type = SCM_CREDTYPE;
        cmp->cmsg_len = CREDSLEN;
        credp = (struct CREDSTRUCT *)CMSG_DATA(cmp);
#if defined(SCM_CREDENTIALS)
        credp->uid = geteuid();
        credp->gid = getegid();
        credp->pid = getpid();
#endif
        buf[1] = 0;
    }
    buf[0] = 0; //null byte flag to recv_ufd()
    if (sendmsg(fd, &msg, 0) != 2){
        return (-1);
    }
    return (0);
}

int
my_recv_fd_v2(int fd, uid_t *uidptr, ssize_t (*userfunc)(int, const void *, size_t)){

    struct cmsghdr *cmp;
    struct CREDSTRUCT *credp;
    char *ptr;
    char buf[MAXLINE];
    struct iovec iov[1];
    struct msghdr msg;
    int nr;
    int newfd = -1;
    int status = -1;


#if defined(CREDOPT)
    const int on = 1;
    if (setsockopt(fd, SOL_SOCKET, CREDOPT, &on, sizeof(int)) < 0){
        err_ret("setsockopt error");
        return (-1);
    }
#endif

    while (true){

        iov[0].iov_base = buf;
        iov[0].iov_len = sizeof(buf);
        msg.msg_iov = iov;
        msg.msg_iovlen = 1;
        msg.msg_name = NULL;
        msg.msg_namelen = 0;
        if (cmptr == NULL && (cmptr = malloc(CONTROLLEN_V2)) == NULL){
            return (-1);
        }
        msg.msg_control = cmptr;
        msg.msg_controllen = CONTROLLEN_V2;
        if ((nr = recvmsg(fd, &msg, 0)) < 0){
            err_ret("recvmsg error");
            return (-1);
        } else if (nr == 0){
            err_ret("connection closed by server");
            return (-1);
        }

        for (ptr = buf; ptr < &buf[nr];){
            if (*ptr++ == 0){
                if (ptr != &buf[nr - 1]){
                    err_dump("message format error");
                }
                status = *ptr & 0xFF;
                if (status == 0){
                    if (msg.msg_controllen != CONTROLLEN_V2){
                        err_dump("status = 0 but no fd");
                    }

                    //process the control data
                    for (cmp = CMSG_FIRSTHDR(&msg); cmp != NULL; cmp = CMSG_NXTHDR(&msg, cmp)){
                        if (cmp->cmsg_level != SOL_SOCKET){
                            continue;
                        }
                        switch (cmp->cmsg_type) {
                            case SCM_RIGHTS:
                                newfd = *(int *)CMSG_DATA(cmp);
                                break;
                            case SCM_CREDTYPE:
                                credp = (struct CREDSTRUCT *)CMSG_DATA(cmp);
                                *uidptr = credp->CR_UID;
                        }
                    }
                } else{
                    newfd = -status;
                }
                nr -= 2;
            }
        }

        if (nr > 0 && (*userfunc)(STDERR_FILENO, buf, nr) != nr){
            return (-1);
        }
        if (status >= 0){ //final data has arrived
            return (newfd); //descriptor or -status
        }
    }
}



























