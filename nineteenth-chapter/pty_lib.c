//
// Created by 王勇椿 on 2020/10/22.
//忽略Solaris中，打开从设备后，可能需要将3个STREAMS模块压入从设备的流中
//
#include "../include/apue.h"
#include <errno.h>
#include <fcntl.h>

int
my_ptym_open(char *pts_name, int pts_namesz){

    char *ptr;
    int fdm, err;

    if ((fdm = posix_openpt(O_RDWR)) < 0){
        return (-1);
    }
    if (grantpt(fdm) < 0){ //grant access to slave
        goto errout;
    }
    if (unlockpt(fdm) < 0){ //clear slave's lock flag
        goto errout;
    }
    if ((ptr = ptsname(fdm)) == NULL){ // get slave's name
        goto errout;
    }

    /**
     * Return name of slave. Null terminate to handle case where strlen(ptr) > pts_namesz
     */
    strncpy(pts_name, ptr, pts_namesz);
    pts_name[pts_namesz - 1] = '\0';
    return (fdm);

    errout:
        err = errno;
        close(fdm);
        errno = err;
        return (-1);
}

int
my_ptys_open(char *pts_name){

    int fds;

    if ((fds = open(pts_name, O_RDWR)) < 0){
        return (-1);
    }

    return (fds);
}

int
my_pty_fork(int *ptrfdm, char *slave_name, int slave_namesz, const struct termios *slave_termios, const struct winsize *slave_winsize){

    int fdm, fds;
    pid_t pid;
    char pts_name[20];

    if ((fdm = my_ptym_open(pts_name, sizeof(pts_name))) < 0){
        err_sys("can't open master pty: %s, error %d", pts_name, fdm);
    }

    if (slave_name != NULL){

        /**
         * Return name of slave. Null terminate to handle case when strlen(pts_name) > slave_namesz
         */
         strncpy(slave_name, pts_name, slave_namesz);
         slave_name[slave_namesz - 1] = '\0';
    }

    if ((pid = fork()) < 0){
        return (-1);
    } else if (pid == 0){ // child

        if (setsid() < 0){
            err_sys("setsid error");
        }

        //System V acquires controlling terminal on open
        if ((fds = my_ptys_open(slave_name)) < 0){
            err_sys("can't open slave pty");
        }
        close(fdm); //all done with master in child

#if defined(BSD)
        //TIOCSCTTY is the BSD way to acquire a controlling terminal
        if (ioctl(fds, TIOCSCTTY, (char *)0) < 0){
                err_sys("TIOCSCTTY error");
        }
#endif
        if (slave_termios != NULL){
            if (tcsetattr(fds, TCSANOW, slave_termios) < 0){
                err_sys("tcsetattr error on slave pty");
            }
        }
        if (slave_winsize != NULL){
            if (ioctl(fds, TIOCSWINSZ, slave_winsize) < 0){
                err_sys("TIOCSWINSZ error on slave pty");
            }
        }

        //从设备文件描述符复制到子进程的标准输入、标准输出、标准错误中。这样不管子进程以后调用exec执行何种程序，它都具有同PTY从设备联系起来的上述3个文件描述符
        if (dup2(fds, STDIN_FILENO) != STDIN_FILENO){
            err_sys("dup2 error to stdin");
        }
        if (dup2(fds, STDOUT_FILENO) != STDOUT_FILENO){
            err_sys("dup2 error to stdout");
        }
        if (dup2(fds, STDERR_FILENO) != STDERR_FILENO){
            err_sys("dup2 error to stderr");
        }
        if (fds != STDIN_FILENO && fds != STDOUT_FILENO && fds != STDERR_FILENO){
            close(fds);
        }
        return (0); //child return o just like fork
    } else{
        *ptrfdm = fdm; //return fd of master
        return (pid); //return child process id
    }
}

