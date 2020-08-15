//
// Created by 王勇椿 on 2020/8/15.
//
//二进制IO

#include "../include/apue.h"

#define NAMESIZE 10
void my_write(void);
void my_read(void);

struct item{
    short count;
    long total;
    char name[NAMESIZE];
};

int main(void){

//    my_write();
    my_read();
}

void my_write(void){

    FILE *fp;
    if ((fp = fopen("../file/binary_io.txt", "a")) == NULL){
        err_sys("fopen file error");
    }

//    float data[10] = {1.2f,2.1f,3.1f,4.1f,5.1f,1.5f,1.6f,6.1f,8.7f,7.8f};
//    if (fwrite(&data[2], sizeof(float), 4, fp) != 4){
//        err_sys("fwrite error");
//    }



    struct item myitem;
    myitem.count = 3;
    myitem.total = 4;
    strcat(myitem.name, "baobao");

    if (fwrite(&myitem, sizeof(struct item), 1, fp) != 1){
        err_sys("fwrite struct error");
    }
}


void my_read(void){


    FILE *fp;
    if ((fp = fopen("../file/binary_io.txt", "r")) == NULL){
        err_sys("fopen error");
    }


    struct item myitem;
    if (fread(&myitem, sizeof(struct item), 1, fp) != 1){
        err_sys("fread error");
    }

    printf("name: %s, total: %ld", myitem.name, myitem.total);
}

