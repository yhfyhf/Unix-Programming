/* read /etc/utmp and list info therein
 * suppress empty records
 * formats time nicely
 */
#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#define SHOWHOST

void show_time(long);
void show_info(struct utmp*);

int main() {
    struct utmp current_record;
    int         utmpfd;
    int         reclen = sizeof(current_record);

    if ( (utmpfd = open(_PATH_UTMP, O_RDONLY)) == -1) {
        perror(_PATH_UTMP);
        exit(1);
    }

    while ( read(utmpfd, &current_record, reclen) == reclen)
        show_info(&current_record);
    close(utmpfd);
    return 0;
}

void show_info(struct utmp *utbufp) {
/*
 * show info()
 *      displays the contents of the utmp struct
 *      in human readable form
 *      displays nothing if record has no user name
 */
    if (utbufp->ut_type != USER_PROCESS)
        return;
    
    printf("% -10.10s", utbufp->ut_name); /* the log name*/
    printf(" ");    
    printf("% -8.8s", utbufp->ut_line); /* the tty */
    printf(" ");
    show_time(utbufp->ut_time);
#ifdef SHOWHOST
    if (utbufp->ut_host[0] != '\0')
        printf("( %s)", utbufp->ut_host);
#endif
    printf("\n");
}

void show_time(long timeval) {
/*
 * displays time in a format fit for human consumption
 * uses ctime to build a string then picks parts out of it
 */
    char *cp;   /* to hold address of time*/
    cp = ctime(&timeval); /* convert time to string */
    printf("% 12.12s", cp+4);
}    

