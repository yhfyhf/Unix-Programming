/* 
 * utmplib.c - functions to buffer reads from utmp file.
 *
 * function are
 *     utmp_open(filename) - open file
 *         returns -1 on error
 *     utmp_next()         - return pointer to next struct
 *         returns NULL on EOF
 *     utmp_close()        - close file
 *
 *  reads NRECS per read and then doles them out from the buffer.
 *
 *  记录了缓冲区所需的变量和函数。
 *  每次要从缓冲区中读数据前，先检查cur_rec的值是否等于num_recs，
 *  如果想等说明缓冲区中已经没有可用数据了，就调用read从硬盘上读数据
 *  来填满缓冲区，在返回数据前，增加cur_rec的值。
 */

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utmp.h>

#define NRECS 16
#define NULLUT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))

static char utmpbuf[NRECS * UTSIZE]; // storage
static int  num_recs;                // num stored 缓冲区的数据个数
static int  cur_rec;                 // next to go
static int  fd_utmp = -1;            // read from

utmp_open(char *filename) {
    fd_utmp = open(filename, O_RDONLY);     // open it
    cur_rec = num_recs = 0;                 // no records yet
    return fd_utmp;
}

struct utmp* utmp_next() {
    struct utmp *recp;
    if (fd_utmp == -1)                                // error
        return NULLUT;
    if (cur_rec == num_recs && utmp_reload() == 0)    // any more?
        return NULLUT;
    recp = (struct utmp*) &utmpbuf[cur_rec * UTSIZE]; // get address of next record
    cur_rec++;
    return recp;
}

int utmp_reload() {
    /* 
     * read next bunch of records into buffer
     */
    int amt_read;                                      // read them in
    amt_read = read(fd_utmp, utmpbuf, NRECS * UTSIZE); // how many did we get
    num_recs = amt_read / UTSIZE;                      // reset pointer
    cur_rec = 0;
    return num_recs;
}

utmp_close() {
    if (fd_utmp != -1)
        close(fd_utmp);
}

