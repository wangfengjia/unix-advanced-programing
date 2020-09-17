//
// Created by 王勇椿 on 2020/9/16.
//

#include "../include/apue.h"
#include "daemonize.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>


void mydaemonize(const char *cmd){

    int i, fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;

    //clear file create mask(文件模式创建屏蔽字)
    umask(0);

    //get maximum number of descriptors
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0){
        err_quit("%s: can't get file limit", cmd);
    }

    //Becoming a session leader to lose controlling TTY
    if ((pid = fork()) < 0){
        err_quit("%s: can't fork", cmd);
    } else if (pid != 0){ //parent process
        exit(0);
    }
    setsid();

    //Ensure future opens allocate controlling TTYs
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0){
        err_quit("%s: can't ignore SIGHUP", cmd);
    }

    if ((pid = fork()) < 0){
        err_quit("%s: can't fork", cmd);
    } else if (pid != 0){
        exit(0);
    }

    /**
     * change the current working directory to root so we won't prevent file systems from being unmounted
     */
     if (chdir("/") < 0){
         err_quit("%s: can't change directory to /", cmd);
     }

     //close all open file descriptors
     if (rl.rlim_max == RLIM_INFINITY){
         rl.rlim_max = 1024;
     }
     for (i = 0; i < rl.rlim_max; i++){
         close(i);
     }

     //打开/dev/null使其具有文件描述符0，1，2，这样任何一个读标准输入，写标出输出或标准错误的库例程都不会产生效果
     fd0 = open("/dev/null", O_RDWR);
     fd1 = dup(fd0);
     fd2 = dup(fd0);

     //初始化日志
     openlog(cmd, LOG_CONS, LOG_DAEMON);
     if (fd0 != 0 || fd1 != 1 || fd2 != 2){
         syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
         exit(1);
     }
}
