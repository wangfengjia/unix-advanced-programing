//
// Created by 王勇椿 on 2020/9/10.
//

#ifndef UNIX_ADVANCED_PROGRAMING_THREAD_PRIVATE_DATA_H
#define UNIX_ADVANCED_PROGRAMING_THREAD_PRIVATE_DATA_H
//线程私有数据。在分配线程私有数据前，要创建和此数据相关联的键，每个键可以关联一个析构函数(线程私有数据一般是通过malloc分配，析构函数一般释放已分配的内存。
// 如果线程在没有释放内存之前就退出，这个线程所属进程就发生了内存泄漏)。这个键可以被进程中的所有线程所共享，但每个线程把这个键与不同的线程特定数据地址进行关联。
//创建新键时，每个线程数据地址设置为空值
//实现线程私有数据的getenv函数

char *thread_private_getenv(const char *);
void print_address(void);


#endif //UNIX_ADVANCED_PROGRAMING_THREAD_PRIVATE_DATA_H
