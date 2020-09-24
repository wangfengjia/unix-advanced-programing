//
// Created by 王勇椿 on 2020/9/24.
//
/**
 * 编写一个程序，每次一页地显示已产生的输出。很多unix系统已经有了分页程序，我们不再需要编写分页程序，只需要调用分页程序就可以了
 * 问题:为了避免先将所有数据写到一个临时文件中，然后再调用分页程序显示该文件
 * 解决办法:通过管道将输出直接送到分页程序。为此，先创建一个管道，fork一个子进程，使子进程的标准输入成为管道的读端，然后调用exec执行分页程序,分页程序会去读取它所在进程的标准输入
 */
#include "../include/apue.h"
#include <sys/wait.h>

#define DEF_PAGER "/bin/more" //default pager program

int
main(int argc, char *argv[]){

    int n;
    int fd[2];
    pid_t pid;
    char *pager, *argv0;
    char line[MAXLINE];
    FILE *fp;

    if (argc != 2){
        err_quit("usage: pipe2 <pathname>");
    }

    if ((fp = fopen(argv[1], "r")) == NULL){
        err_sys("can't open %s", argv[1]);
    }
    if (pipe(fd) < 0){
        err_sys("pipe error");
    }

    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid > 0){
        close(fd[0]);

        //parent copy argv[1] to pipe
        while (fgets(line, MAXLINE, fp) != NULL){
            n = strlen(line);
            if (write(fd[1], line, n) != n){
                err_sys("write error to pipe");
            }
        }

        if (ferror(fp)){
            err_sys("fgets error");
        }

        //close write end of pipe for reader
        close(fd[1]);

        if (waitpid(pid, NULL, 0) < 0){
            err_sys("waitpid error");
        }
        exit(0);
    } else{
        close(fd[1]);
        if (fd[0] != STDIN_FILENO){
            if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO){
                err_sys("dup2 error to stdin");
            }
            // don't need this after dup2
            close(fd[0]);
        }
        //get arguments for execl()
        if ((pager = getenv("PAGER")) == NULL){
            pager = DEF_PAGER;
        }
        if ((argv0 = strrchr(pager, '/')) != NULL){
            argv0++; //step past rightmost slash
        } else{
            argv0 = pager; //no slash in pager
        }

        if (execl(pager, argv0, (char *)0) < 0){
            err_sys("execl error for %s", pager);
        }
    }

    exit(0);
}























