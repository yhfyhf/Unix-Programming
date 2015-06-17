/*
 * ls -al
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

void do_ls(char[]);
void do_stat(char *);
void show_file_info(char *, struct stat*);
void mode_to_letters(int, char[]);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

int main(int argc, char *argv[]) {
    if (argc == 0 || argc == 1) {
        do_ls(".");
    }
    else {
        while (--argc) {
            printf("%s\n", *++argv);
            do_ls(*argv);
        }
    }
}

void do_ls(char dirname[]) {
    /*
     * list files in directory `dirname`
     */
    DIR           *dir_ptr;  // the directory
    struct dirent *direntp;  // each entry

    if ((dir_ptr = opendir(dirname)) == NULL)
        fprintf(stderr, "ls: cannot open %s\n", dirname);
    else {
        while ((direntp = readdir(dir_ptr)) != NULL) {
            do_stat(direntp->d_name);
        }
        closedir(dir_ptr);
    }
}

void do_stat(char *filename) {
    struct stat info;
    if (stat(filename, &info) == -1)   // cannot stat
        perror(filename);
    else 
        show_file_info(filename, &info);
}

void show_file_info(char *filename, struct stat *info_p) {
    /*
     * display info of filename
     */
    char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
    void mode_to_letters();
    char modestr[11];

    mode_to_letters(info_p->st_mode, modestr);

    printf("%s ", modestr);
    printf("%4d ", (int) info_p->st_nlink);        // number of hard links
    printf("%-8s ", uid_to_name(info_p->st_uid));  // User ID
    printf("%-8s ", gid_to_name(info_p->st_gid));  // Group ID
    printf("%8ld ", (long) info_p->st_size);       // filesize
    printf("%.12s ", 4+ctime(&info_p->st_mtime));  // last data modification time
    printf("%s\n", filename);
}

/*
 * utils
 */

void mode_to_letters(int mode, char str[]) {
    strcpy(str, "----------");

    if (S_ISDIR(mode)) str[0] = 'd';  // is directory?
    if (S_ISCHR(mode)) str[0] = 'c';  // or character?
    if (S_ISBLK(mode)) str[0] = 'b';  // or block?
    
    /* 3 bits for user */   
    if (mode & S_IRUSR) str[1] = 'r';
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';

    /* 3 bits for group */
    if (mode & S_IRGRP) str[4] = 'r';
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';

    /* 3 bits for other */
    if (mode & S_IROTH) str[7] = 'r';
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXOTH) str[9] = 'x';
}


#include <pwd.h>

char *uid_to_name(uid_t uid) {
    /*
     * returns pointer to username assocaited with uid
     */
    struct passwd *getpwuid(), *pw_ptr;
    static char numstr[10];

    if ((pw_ptr = getpwuid(uid)) == NULL) {
        sprintf(numstr, "%d", uid);
        return numstr;
    }
    else 
        return pw_ptr->pw_name;
}

#include <grp.h>

char *gid_to_name(gid_t gid) {
    /*
     * returns pointer to group number gid.
     */
    struct group *getgrgid(), *grp_ptr;
    static char numstr[10];

    if ((grp_ptr = getgrgid(gid)) == NULL) {
        sprintf(numstr, "%d", gid);
        return numstr;
    }
    else
        return grp_ptr->gr_name;
}

