//
// Created by 王勇椿 on 2020/10/27.
//数据库函数库
//

#ifndef UNIX_ADVANCED_PROGRAMING_DB_LIB_H
#define UNIX_ADVANCED_PROGRAMING_DB_LIB_H

typedef void * DBHANDLE;

DBHANDLE db_open(const char *, int, ...);
void db_close(DBHANDLE);
char *db_fetch(DBHANDLE, const char *);
int db_store(DBHANDLE, const char *, const char *, int);
int db_delete(DBHANDLE, const char *);
void db_rewind(DBHANDLE);
char *db_nextrec(DBHANDLE, char *);

//flags for db_store
#define DB_INSERT  1
#define DB_REPLACE 2
#define DB_STORE   3

//implementation limits
#define IDXLEN_MIN 6    //key,sep,start,sep,length, \n
#define IDXLEN_MAX 1024 //arbitrary
#define DATLEN_MIN 2    //data byte,newline
#define DATLEN_MAX 1024 //arbitrary


#endif //UNIX_ADVANCED_PROGRAMING_DB_LIB_H
