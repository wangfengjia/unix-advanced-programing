//
// Created by 王勇椿 on 2020/8/13.
//
//遍历目录

#include <dirent.h>
#include <limits.h>
#include "../include/apue.h"

#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3
#define FTW_NS 4

typedef int my_func(const char *, const struct stat *, int);

static my_func myfunc;
//static int my_func(const char *, const struct stat *, int);
//static int myftw(char *, int (*ptr)(const char *, struct stat*, int));

static int myftw(char *, my_func *);
static int dopath(my_func *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;
static char *fullpath;
static size_t pathlen;

int main(int argc, char *argv[]){

    int ret;
    if (argc != 2){
        err_quit("usage: ftw <starting-pathname>");
    }

    ret = myftw(argv[1], myfunc);
    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
    if (ntot == 0){
        ntot = 1;
    }

    printf("regular files = %7ld, %5.2f %%\n", nreg, nreg * 100.0 / ntot);
    printf("regular directories = %7ld, %5.2f %%\n", ndir, ndir * 100.0 / ntot);
    printf("block special = %7ld, %5.2f %%\n", nblk, nblk * 100.0 / ntot);
    printf("char special = %7ld, %5.2f %%\n", nchr, nchr * 100.0 / ntot);
    printf("FIFOs = %7ld, %5.2f %%\n", nfifo, nfifo * 100.0 / ntot);
    printf("symbolic links = %7ld, %5.2f %%\n", nslink, nslink * 100.0 / ntot);
    printf("sockets = %7ld, %5.2f %%\n", nsock, nsock * 100.0 / ntot);

    exit(ret);
}

static int myftw(char *pathname, my_func *func){

    fullpath = path_alloc(&pathlen);
    if (pathlen <= strlen(pathname)){
        pathlen = strlen(pathname) * 2;
        if ((fullpath = realloc(fullpath, pathlen)) == NULL){
            err_sys("realloc failed");
        }
    }

    strcpy(fullpath, pathname);
    return dopath(func);
}

static int dopath(my_func *func){

    struct stat statbuff;
    struct dirent *dirent;
    DIR *dir;
    int ret, n;


    if (lstat(fullpath, &statbuff) < 0){ //lstat error
        return (func(fullpath, &statbuff, FTW_NS));
    }

    //not a directory
    if (S_ISDIR(statbuff.st_mode) == 0){
        return (func(fullpath, &statbuff, FTW_F));
    }

    //is a directory, first call the func() for the directory
    if ((ret = func(fullpath, &statbuff, FTW_D)) != 0){
        return ret;
    }

    n = strlen(fullpath);
    if (n + NAME_MAX + 2 > pathlen){
        pathlen *= 2;
        if ((fullpath = realloc(fullpath, pathlen)) == NULL){
            err_sys("realloc failed");
        }
    }

    fullpath[n++] = '/';
    fullpath[n] = 0;
    if ((dir = opendir(fullpath)) == NULL){
        return (func(fullpath, &statbuff, FTW_DNR));
    }

    while ((dirent = readdir(dir)) != NULL){
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0){
            continue;
        }
        strcpy(&fullpath[n], dirent->d_name);
        if ((ret = dopath(func)) != 0){
            break;
        }
    }
    fullpath[n - 1] = 0;
    if (closedir(dir) < 0){
        err_ret("can not close directory %s", fullpath);
    }

    return ret;
}


static int myfunc(const char *pathname, const struct stat *statptr, int type){

    switch (type) {
        case FTW_F:
            switch (statptr->st_mode & S_IFMT) {
                case S_IFREG:
                    nreg++;
                    break;
                case S_IFBLK:
                    nblk++;
                    break;
                case S_IFCHR:
                    nchr++;
                    break;
                case S_IFIFO:
                    nfifo++;
                    break;
                case S_IFLNK:
                    nslink++;
                    break;
                case S_IFSOCK:
                    nsock++;
                    break;
                case S_IFDIR:
                    err_dump("for s_ifdir for %s", pathname);
            }
            break;
        case FTW_D:
            ndir++;
            break;
        case FTW_DNR:
            err_ret("can not read directory %s", pathname);
            break;
        case FTW_NS:
            err_ret("stat error for %s", pathname);
            break;
        default:
            err_dump("unknown type %d for pathname %s", type, pathname);
    }

    return 0;
}

