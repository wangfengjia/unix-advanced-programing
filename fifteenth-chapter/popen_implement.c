//
// Created by 王勇椿 on 2020/9/24.
//
#include "popen_implement.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

static pid_t *childpid = NULL;
static int maxfd;

FILE *my_popen(const char *cmdstring, const char *type){

    int i;
    int pfd[2];
    pid_t pid;
    FILE *fp;
    errno = 0;

    //only allow "r" or "w"
    if ((type[0] != 'r' && type[0] != 'w') || type[1] != 0){
        errno = EINVAL;
        return (NULL);
    }

    //first time through
    if (childpid == NULL){
        maxfd = open_max();
        if ((childpid = calloc(maxfd, sizeof(pid_t))) == NULL){
            return NULL;
        }
    }

    if (pipe(pfd) < 0){
        return (NULL); //errno set by pipe
    }
    if (pfd[0] >= maxfd || pfd[1] >= maxfd){
        close(pfd[0]);
        close(pfd[1]);
        errno = EMFILE;
        return NULL;
    }

    if ((pid = fork()) < 0){
        return (NULL); //errno set by fork
    } else if (pid == 0){ //child process
        //type值为"r"时，返回的文件指针是指向子进程的标准输出，子进程往其对应的标准输出写，其他进程读取此进程的标准输出
        if (*type == 'r'){
            close(pfd[0]);
            if (pfd[1] != STDOUT_FILENO){
                dup2(pfd[1], STDOUT_FILENO);
                close(pfd[1]);
            }
        } else{
            close(pfd[1]);
            if (pfd[0] != STDIN_FILENO){
                dup2(pfd[0], STDIN_FILENO);
                close(pfd[0]);
            }
        }

        //close all descriptors in childpid[]
        for (i = 0; i < maxfd; i++){
            if (childpid[i] > 0){
                close(i);
            }
        }

        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        _exit(127);
    }

    //parent continue
    if (*type == 'r'){
        //关闭管道的写端
        close(pfd[1]);
        if ((fp = fdopen(pfd[0], type)) == NULL){
            return (NULL);
        }
    } else{
        //关闭管道的读端
        close(pfd[0]);
        if ((fp = fdopen(pfd[1], type)) == NULL){
            return (NULL);
        }
    }

    //remember child pid for this fd
    childpid[fileno(fp)] = pid;
    return fp;
}

int
my_pclose(FILE *fp){

    int fd, stat;
    pid_t pid;
    errno = 0;

    //popen() has never been called
    if (childpid == NULL){
        errno = EINVAL;
        return (-1);
    }

    //invalid file descriptor
    fd = fileno(fp);
    if (fd >= maxfd){
        errno = EINVAL;
        return (-1);
    }

    //fp wasn't opened by popen()
    if ((pid = childpid[fd]) == 0){
        errno = EINVAL;
        return (-1);
    }

    childpid[fd] = 0;
    if (fclose(fp) == EOF){
        return (-1);
    }

    //error other than EINTR from waitpid()
    while (waitpid(pid, &stat, 0) < 0){
        if (errno != EINTR){
            return (-1);
        }
    }

    //return child's termination status
    return (stat);
}

