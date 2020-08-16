//
// Created by 王勇椿 on 2020/8/15.
//
//组文件

#include <grp.h>
#include "../include/apue.h"

struct group *my_getgrnam(char *name);

int main(void){

    struct group *gr;

    if ((gr = getgrnam("staff")) == NULL){
        err_sys("getgrnam error");
    }

    printf("name: %s, password: %s\n", gr->gr_name, gr->gr_passwd);

    struct group *newgroup = my_getgrnam("staff");
    printf("name: %s, password: %s\n", newgroup->gr_name, newgroup->gr_passwd);
}


struct group *my_getgrnam(char *name){

    struct group *gr;

    setgrent();
    while ((gr = getgrent()) != NULL){
        if (strcmp(name, gr->gr_name) == 0){
            break;
        }
    }
    endgrent();
    return gr;
}


