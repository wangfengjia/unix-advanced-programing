//
// Created by 王勇椿 on 2020/9/17.
//

#ifndef UNIX_ADVANCED_PROGRAMING_SINGLETON_DAEMONIZE_PROCESS_H
#define UNIX_ADVANCED_PROGRAMING_SINGLETON_DAEMONIZE_PROCESS_H
//单实例守护进程:利用文件和记录锁来保证一个守护进程在任一时刻只有一个副本(实例)在运行
//每一个守护进程创建一个有固定名字的文件，在这个文件的整体上加写锁，那么只允许创建一把这样的写锁。在此之后创建写锁的尝试都会失败
//这向后续守护进程副本指明已有一个副本在运行

#define LOCKFILE "/home/vagrant/c-learn/unix-advanced-programing/daemon.pid"
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)
#define BUFFER_LENGTH 16

int already_running(void);
#endif //UNIX_ADVANCED_PROGRAMING_SINGLETON_DAEMONIZE_PROCESS_H
