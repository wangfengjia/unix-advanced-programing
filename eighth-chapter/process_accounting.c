//
// Created by 王勇椿 on 2020/8/20.
//

#include "../include/apue.h"
#include <sys/acct.h>

#if defined(BSD)
#define acct acctv2
#define ac_flag ac_trailer.ac_flag
#define FMT "%-*.*s e = %.0f, chars = %.0f, %c %c %c\n"
#elif defined(HAS_AC_STAT)
#define FMT "%-*.*s e = %6ld, chars = %71d, stat = %3u: %c %c %c\n"
#else
#define FMT "%-*.*s e = %6ld, chars = %71d, %c %c %c %c\n"
#endif

#if defined(LINUX)
#define acct acctv3
#endif

#if !defined(HAS_ACORE)
#define ACORE 0
#endif
#if !defined(HAS_AXSIG)
#define AXSIG 0
#endif
static unsigned long compt2ulong(comp_t);


#if defined(BSD)
static unsigned long compt2ulong(comp_t comtime){

    unsigned long val;
    int exp;

    val = comtime & 0x1fff;
    exp = (comtime >> 13) & 7;
    while (exp-- > 0){
        val *= 8;
    }
    return val;
}
#endif

int main(int argc, char *argv[]){

    struct acct acdata;
    FILE *fp;

    if (argc != 2){
        err_quit("usage: pracct filename");
    }

    if ((fp = fopen(argv[1], "r")) == NULL){
        err_sys("fopen error");
    }
    while (fread(&acdata, sizeof(struct acct), 1, fp) == 1){
        printf(FMT, (int)sizeof(acdata.ac_comm), (int)sizeof(acdata.ac_comm), acdata.ac_comm,
#if defined(BSD)
        acdata.ac_etime, acdata.ac_io,
#else
        compt2ulong(acdata.ac_etime), compt2ulong(acdata.ac_io),
#endif
#if defined(HAS_AC_STAT)
        (unsigned char)acdata.ac_stat,
#endif
        acdata.ac_flag & ACORE ? 'D' :  ' ',
        acdata.ac_flag & AXSIG ? 'X' : ' ',
        acdata.ac_flag & AFORK ? 'F' : ' ',
        acdata.ac_flag & ASU ? 'S' : ' '
        );
    }

    if (ferror(fp)){
        err_sys("read error");
    }
    exit(0);
}


