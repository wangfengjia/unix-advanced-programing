//
// Created by 王勇椿 on 2020/8/15.
//

#include <pwd.h>
#include <stddef.h>
#include <string.h>
#include "../include/apue.h"

//getpwnam函数的一个实现
struct passwd *my_getpwnam(char *);

int main(void){


//    struct passwd *pas = getpwnam("wangyongchun");
    struct passwd *user = my_getpwnam("wangyongchun");
    printf("name: %s, password: %s\n", user->pw_name, user->pw_passwd);


}

struct passwd *my_getpwnam(char *name){

    struct passwd *pwd;
    //保护性措施，反绕有关文件确保它们定位到开始处
    setpwent();
    while ((pwd = getpwent()) != NULL){
        if (strcmp(name, pwd->pw_name) == 0){
            break;
        }
    }
    endpwent();
    return pwd;
}
