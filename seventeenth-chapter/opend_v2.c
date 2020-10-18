//
// Created by 王勇椿 on 2020/10/18.
//
#include <sys/select.h>
#include <poll.h>
#include "opend_v2.h"
#include <stdbool.h>
#include <fcntl.h>

#define NALLOC 10 //client's struct to alloc/realloc for
static int unused_element = 0;

//alloc more entries in the client[] array
static void client_alloc(void);
static struct pollfd *grow_pollfd(struct pollfd *, int *);

static void client_alloc(void){

    int i;

    if (client == NULL){
        client = malloc(NALLOC * sizeof(Client));
    } else{
        client = realloc(client, (client_size + NALLOC) * sizeof(Client));
    }

    if (client == NULL){
        err_sys("can't alloc for client array");
    }

    //initialize the new entries
    for (i = client_size; i < client_size + NALLOC; i++){
        client[i].fd = -1;
    }

    client_size += NALLOC;
    unused_element += NALLOC;
}

/**
 * Called by loop() when connection request from a new client arrives
 * @param fd
 * @param uid
 * @return
 */
int
client_add(int fd, uid_t uid){

    int i;
    int index = 0;

    if (client == NULL){
        client_alloc();
    }

    //client array full, time to realloc for more
    if (unused_element == 0){
        client_alloc();
    }

    for (i = 0; i < client_size; i++){
        if (client[i].fd == -1){
            client[i].fd = fd;
            client[i].uid = uid;
            --unused_element;
            index = i;
        }
    }

    return index;
}

/**
 * called by loop() when we're done with a client
 * @param fd
 */
void
client_del(int fd){

    int i;
    for (i = 0; i < client_size; i++){
        if (client[i].fd == fd){
            client[i].fd = -1;
            ++unused_element;
            return;
        }
    }

    log_quit("can't find client entry for fd %d", fd);
}

/**
 * 服务器进程的无限循环(select版本)
 */
void
loop(void){

    int i, n, maxfd, maxi, listenfd, clifd, nread;
    char buf[MAXLINE];
    uid_t uid;
    fd_set rset;
    /**
     * 用allset描述符集跟踪当前使用的描述符。当新客户进程连接至服务器进程时，会打开此描述符集的相应位。当该客户进程终止时，会关闭相应位。
     */
    fd_set allset;

    FD_ZERO(&allset);

    //obtain fd to listen for client requests on
    if ((listenfd = serv_listen(CS_OPEN)) < 0){
        log_sys("serv_listen error");
    }
    FD_SET(listenfd, &allset);
    maxfd = listenfd;
    maxi = -1;

    while (true){

        rset = allset; // rset gets modified each time around
        if ((n = select(maxfd + 1, &rset, NULL, NULL, NULL)) < 0){
            log_sys("select error");
        }

        //select返回后有两种情况，一种是有新的连接请求到来，另外一种是已经连接的客户进程发送了数据到服务器进程，有数据可以读取
        if (FD_ISSET(listenfd, &rset)){
            //accept new client request
            if ((clifd = serv_accept(listenfd, &uid)) < 0){
                log_sys("serv_accept error: %d", clifd);
            }
            i = client_add(clifd, uid);
            FD_SET(clifd, &allset);
            if (clifd > maxfd){
                maxfd = clifd; // max fd for select()
            }
            if (i > maxi){
                maxi = i; // max index in client[] array
            }
            log_msg("new connection: uid %d, fd %d", uid, clifd);
            continue;
        }

        //有已经与客户进程建立连接的套接字有数据可读
        for (i = 0; i <= maxi; i++){
            if ((clifd = client[i].fd) < 0){
                continue;
            }
            if (FD_ISSET(clifd, &rset)){
                //read argument buffer from client
                if ((nread = read(clifd, buf, MAXLINE)) < 0){
                    log_sys("read error on fd %d", clifd);
                } else if (nread == 0){ //客户进程已终止
                    log_msg("closed: uid %d, fd %d", client[i].uid, client[i].uid);
                    client_del(clifd);
                    FD_CLR(clifd, &allset);
                    close(clifd);
                } else{ //handle client's request
                    handle_request_v2(buf, nread, clifd, client[i].uid);
                }
            }
        }
    }
}

static struct pollfd *grow_pollfd(struct pollfd *pfd, int *maxfd){

    int i;
    int oldmax = *maxfd;
    int newmax = oldmax + NALLOC;

    if ((pfd = realloc(pfd, newmax * sizeof(struct pollfd))) == NULL){
        err_sys("realloc error");
    }

    for (i = oldmax; i < newmax; i++){
        pfd[i].fd = -1;
        pfd[i].events = POLLIN;
        pfd[i].revents = 0;
    }

    *maxfd = newmax;
    return (pfd);
}

/**
 * loop()函数的poll版本
 */
void
loop_v2(void){

    int i, listenfd, clifd, nread;
    char buf[MAXLINE];
    uid_t uid;
    struct pollfd *pollfd;
    int numfd = 1;
    int maxfd = NALLOC;

    if ((pollfd = malloc(NALLOC * sizeof(struct pollfd))) == NULL){
        err_sys("malloc error");
    }
    for ( i = 0; i < NALLOC; i++){
        pollfd[i].fd = -1;
        pollfd[i].events = POLLIN;
        pollfd[i].revents = 0;
    }


    //创建与客户进程连接的端点
    if ((listenfd = serv_listen(CS_OPEN)) < 0){
        log_sys("serv_listen error");
    }
    client_add(listenfd, 0); //use [0] for listenfd
    pollfd[0].fd = listenfd;

    while (true){

        if (poll(pollfd, numfd, -1) < 0){
            log_sys("poll error");
        }
        //新连接请求
        if (pollfd[0].revents & POLLIN){
            if ((clifd = serv_accept(listenfd, &uid)) < 0){
                log_sys("serv_accept error: %d", clifd);
            }
            client_add(clifd, uid);

            //possibly increase the size of the pollfd array
            if (numfd == maxfd){
                pollfd = grow_pollfd(pollfd, &maxfd);
            }
            pollfd[numfd].fd = clifd;
            pollfd[numfd].events = POLLIN;
            pollfd[numfd].revents = 0;
            ++numfd;
            log_msg("new connection:uid %d, fd %d", uid, clifd);
        }

        //有数据可读或者是客户进程已关闭连接
        for (i = 0; i < numfd; i++){

            if (pollfd[i].revents & POLL_HUP){
                goto hungup;
            } else if (pollfd[i].revents & POLLIN){
                //read argument buffer from client
                if ((nread = read(pollfd[i].fd, buf, MAXLINE)) < 0){
                    log_sys("read error on fd %d", pollfd[i].fd);
                } else if (nread == 0){
hungup:
                    //the client closed the connection
                    log_msg("closed: uid %d, fd %d", client[i].uid, pollfd[i].fd);
                    client_del(pollfd[i].fd);
                    close(pollfd[i].fd);
                    if (i < (numfd - 1)){
                        //将pollfd的最后一个元素移动到已经断开连接的pollfd的位置,保证数组里面没有无效元素
                        pollfd[i].fd = pollfd[numfd - 1].fd;
                        pollfd[i].events = pollfd[numfd - 1].events;
                        pollfd[i].revents = pollfd[numfd - 1].revents;
                        i--; // 重新check移动到被删除元素位置的pollfd，是否有事件发生
                    }
                } else{
                    handle_request_v2(buf, nread, pollfd[i].fd, client[i].uid);
                }
            }
        }
    }
}

void
handle_request_v2(char *buf, int nread, int clifd, uid_t uid){

    int newfd;
    if (buf[nread - 1] != 0){
        snprintf(errmsg_v2, MAXLINE - 1, "request from uid %d not null terminated: %*.*s\n", uid, nread, nread, buf);
        send_err(clifd, -1, errmsg_v2);
        return;
    }

    log_msg("request: %s, from uid %d", buf, uid);

    //parse arguments, set option
    if (buf_args(buf, client_args) < 0){
        send_err(clifd, -1, errmsg_v2);
        log_msg(errmsg_v2);
        return;
    }

    if ((newfd = open(pathname_v2, oflag_v2)) < 0){
        snprintf(errmsg_v2, MAXLINE - 1, "can't open %s: %s\n", pathname_v2, strerror(errno));
        send_err(clifd, -1, errmsg_v2);
        log_msg(errmsg_v2);
        return;
    }

    //send the descriptor
    if (send_fd(clifd, newfd) < 0){
        log_sys("send_fd error");
    }
    log_msg("send fd %d over fd %d for %s", newfd, clifd, pathname_v2);
    close(newfd);
}






