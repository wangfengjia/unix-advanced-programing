//
// Created by 王勇椿 on 2020/8/31.
//

//处理信号集的各个函数的实现
#include <signal.h>
#include <errno.h>

#define SIGBAD(signo)((signo) <= 0 || (signo) >= NSIG)

int my_sigaddset(sigset_t *, int);
int my_sigdelset(sigset_t *, int);
int my_sigismember(sigset_t *, int);

int my_sigaddset(sigset_t *sigset, int signo){

    errno = 0;
    if (SIGBAD(signo)){
        errno = EINVAL;
        return -1;
    }

    //将signo对应的信号的位设置为1
    *sigset |= 1 << (signo - 1);
    return 0;
}

int my_sigdelset(sigset_t *sigset, int signo){

    errno = 0;
    if (SIGBAD(signo)){
        errno = EINVAL;
        return -1;
    }

    //将signo对应的信号的位设置为0
    *sigset &= ~(1 << (signo - 1));
    return 0;
}

int my_sigismember(sigset_t *sigset, int signo){

    if (SIGBAD(signo)){
        errno = EINVAL;
        return -1;
    }

    return ((*sigset & (1 << (signo - 1))) != 0);
}




