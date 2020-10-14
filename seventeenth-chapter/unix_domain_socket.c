//
// Created by 王勇椿 on 2020/10/13.
//
//unix域套接字，用于运行在同一个计算机上的两个进程之间通信，在这种场景中，比因特网域套接字的效率更高，原因是unix域套接字只是复制数据，并不执行协议处理，
//不需要添加和删除网络报头，无需计算校验和，不要产生顺序号，无需发送确认报文
/**
 * 例子:XSI消息队列有一个使用问题:不能和poll和select一起工作，因为消息队列没有关联的文件描述符，但是套接字描述符也是文件描述符,可以用套接字来通知。
 * 对每个消息队列使用一个线程，每个线程都会在msgrcv调用中阻塞，当消息到达时，线程会把它写入一个unix域套接字的一端。当poll指示套接字可以读取数据时，
 * 应用程序会使用这个套接字的另外一端来接收这个消息
 */

#include "../include/apue.h"
#include <poll.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/socket.h>
#include <stdbool.h>

#define NQ 3
#define MAXSIZE 512
#define KEY 0x123 /**key for first message queue*/

struct threadinfo{
    int qid;
    int fd;
};

struct mymesg{
    long mtype;
    char mtext[MAXSIZE];
};

void *helper(void *);

void *helper(void *arg){

    int n;
    struct mymesg m;
    struct threadinfo *tip = arg;

    while (true){
        memset(&m, 0, sizeof(m));
        if ((n = msgrcv(tip->qid, &m, MAXSIZE, 0, MSG_NOERROR)) < 0){
            err_sys("msgrcv error");
        }
        if (write(tip->fd, m.mtext, n) < 0){
            err_sys("write error");
        }
    }

    return ((void *)0);
}

int
main(void){

    int i, n, err;
    int fd[2];
    int qid[NQ];
    struct pollfd pfd[NQ];
    struct threadinfo ti[NQ];
    pthread_t tid[NQ];
    char buf[MAXSIZE];


    for (i = 0; i < NQ; i++){
        if ((qid[i] = msgget((KEY + i), IPC_CREAT|0666)) < 0){
            err_sys("msgget error");
        }

        printf("queue ID %d is %d\n", i, qid[i]);
        //unix域数据报套接字
        if (socketpair(AF_UNIX, SOCK_DGRAM, 0, fd) < 0){
            err_sys("socketpair error");
        }
        pfd[i].fd = fd[0];
        pfd[i].events = POLLIN;
        ti[i].qid = qid[i];
        ti[i].fd = fd[1];

        if ((err = pthread_create(&tid[i], NULL, helper, &ti[i])) != 0){
            err_exit(err, "pthread_create error");
        }
    }

    while (true){
        if (poll(pfd, NQ, -1) < 0){
            err_sys("poll error");
        }
        for (i = 0; i < NQ; i++){
            if (pfd[i].revents & POLLIN){
                if ((n = read(pfd[i].fd, buf, sizeof(buf))) < 0){
                    err_sys("read error");
                }
                buf[n] = 0;
                printf("queue id %d, message %s\n", qid[i], buf);
            }
        }
    }

    exit(0);
}


















