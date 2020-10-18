//
// Created by 王勇椿 on 2020/10/17.
//

#ifndef UNIX_ADVANCED_PROGRAMING_OPEND_H
#define UNIX_ADVANCED_PROGRAMING_OPEND_H

//open服务器进程
#include "../include/apue.h"
#include <errno.h>

#define CL_OPEN "open"
#define MAXARGC 30 //max number of arguments in buf
#define WHITE " \t\n" //white space for tokenizing arguments

extern char errmsg[]; //error message string return to client
extern int oflag;
extern char *pathname; //of file to open() for client

//验证客户进程传送的参数个数是否正确，然后将路径名和打开模式存储在全局变量中
int cli_args(int, char **);
//处理客户进程打开文件的请求
void handle_request(char *, int, int);

/**
 * buf[] contains white-space-separated arguments, We convert it to an argv-style array of pointer, and call the user's function (opfunc)
 * to process the array. we return -1 if there is a problem parsing buf, else we return whatever optfunc() returns. Note that user's buf[]
 * array is modified (null placed after each token)
 * @param optfunc
 * @return
 */
int cli_buf_args(char *buf, int (*optfunc)(int, char **));
#endif //UNIX_ADVANCED_PROGRAMING_OPEND_H
