//
// Created by 王勇椿 on 2020/10/21.
//

#ifndef UNIX_ADVANCED_PROGRAMING_TERMINAL_IO_LIB_H
#define UNIX_ADVANCED_PROGRAMING_TERMINAL_IO_LIB_H
//终端I/O自己编写的类库
#define MAX_PASS_LEN 8
//函数isatty的实现,istty判断一个文件描述符引用的是不是终端设备
int my_isatty(int);
//返回在参数fd文件描述符上打开的终端设备的路径名。实现逻辑:读/dev目录，寻找具有相同设备号和i节点编号的表项。
// 每个文件系统都有唯一的设备号(stat结构中的st_dev字段)，文件系统中的每个目录项都有唯一的i节点编号
char *my_ttyname(int);

char *getpass(const char *);
#endif //UNIX_ADVANCED_PROGRAMING_TERMINAL_IO_LIB_H
