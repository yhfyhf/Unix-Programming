/**
 * ls1.c
 * list files in certain directory
 * TODO:
 *   sort
 *   format
 *   list dotfile
 *   -l
 */
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void do_ls(char []);

int main(int argc, char *argv[]) {
    if (argc == 0 || argc == 1)
        do_ls(".");
    else 
        while (--argc) {
            printf("%s:\n", *++argv);
            do_ls(*argv);
        }
    return 0;
}

void do_ls(char dirname[]) {
    /*
     * list files in directory `dirname`
     */
    DIR *dir_ptr;            // the directory
    struct dirent *direntp;  // each entry

    if ((dir_ptr = opendir(dirname)) == NULL)
        fprintf(stderr, "ls: cannot open %s\n", dirname);
    else {
        while ((direntp = readdir(dir_ptr)) != NULL)
            printf("%s\n", direntp->d_name);
        closedir(dir_ptr);
    }
}

