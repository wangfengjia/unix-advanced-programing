//
// Created by 王勇椿 on 2020/9/7.
//
//屏障:协调多个线程并行工作的同步机制。屏障允许线程等待，直到所有合作线程到达某一点，然后从这点继续执行
//pthread_barrier_init函数初始化屏障，可以指定必须到达屏障的线程数目
//线程可以调用pthread_barrier_wait函数来表明调用线程已经完成工作，等待其他线程赶上来。如果在调用此函数，屏障计数(到达屏障的线程数目)未满足条件，调用线程会进入休眠状态

//例子:有一个大的数据集需要排序，将这个数据集分解成多个小的数据集，在每个线程上对一小数据集进行排序，所有线程排完序以后有进行序数组的合并
#include "../include/apue.h"
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>
#include <stdlib.h>

#define NTHR 16 //线程数组
#define NUMNUM 80000000L //需要排序的数据个数
#define TNUM (NUMNUM / NTHR) //每个线程需要排序的数据个数

long nums[NUMNUM];
long snums[NUMNUM];

pthread_barrier_t b;
//extern int qsort(void *, size_t, size_t, int (*)(const void *, const void *));
int complong(const void *, const void *);
void *thr1_function(void *);
void merge();

int complong(const void *arg1, const void *arg2){

    long l1 = *(long *)arg1;
    long l2 = *(long *)arg2;

    if (l1 == l2){
        return 0;
    } else if (l1 < l2){
        return -1;
    } else{
        return 1;
    }
}

void *thr1_function(void *arg){

    long idx = (long)arg;
    qsort(&nums[idx], TNUM, sizeof(long), complong);
    pthread_barrier_wait(&b);

    return ((void *)0);
}


/**
 * 合并多个从小到大排序的数组，通过每次找到这几个数组的最小元素放到新的数组，最后新数组就是一个有序数组，对所有元素都排了序
 */
void merge(){

    long idx[NTHR];
    long i, minidx, sidx, min_value;

    //每个数组的比较游标
    for (i = 0; i < NTHR; i++){
        idx[i] = i * TNUM;
    }

    for (sidx = 0; sidx < NUMNUM; sidx++){
        min_value = LONG_MAX;
        //每次通过比较，找到多个数组中的最小元素
        for (i = 0; i < NTHR; i++){
            if ((idx[i] < (i + 1) * TNUM) && (nums[idx[i]] < min_value)){
                min_value = nums[idx[i]];
                minidx = i; //最小值在第几个线程
            }
        }
        snums[sidx] = min_value;
        idx[minidx]++;
    }
}

int main(void){

    unsigned long i;
    struct timeval start, end;
    long long startusec, endusec;
    double elapsed;
    int err;
    pthread_t tid;

    //Create the initial set odf numbers to sort
    srandom(1);
    for (i = 0; i < NUMNUM; i++){
        nums[i] = random();
    }
    //create 8 threads to sort numbers
    gettimeofday(&start, NULL);
    pthread_barrier_init(&b, NULL, NTHR + 1);
    for (i = 0; i < NTHR; i++){
        err = pthread_create(&tid, NULL, thr1_function, (void *)(i * TNUM));
        if (err != 0){
            err_exit(err, "can't create thread");
        }
    }
    pthread_barrier_wait(&b);
    merge();
    gettimeofday(&end, NULL);

    //print sorted list
    startusec = start.tv_sec * 1000000 + start.tv_usec;
    endusec = end.tv_sec * 1000000 + end.tv_usec;
    elapsed = (double)(endusec - startusec) / 1000000.0;
    printf("sort took %.4f seconds\n", elapsed);
//    for (i = 0; i < NUMNUM; i++){
//        printf("%ld\n", snums[i]);
//    }

    exit(0);
}




















