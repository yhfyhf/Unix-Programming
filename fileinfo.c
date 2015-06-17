/*
 * use stat to print file infos
 */

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

void show_stat_info(char*, struct stat*);

int main(int argc, char *argv[]) {
    struct stat info;          // buffer for file info

    if (argc > 1)
        if (stat(argv[1], &info) != -1) {
            show_stat_info(argv[1], &info);
            return 0;
        }
        else 
            perror(argv[1]);
    return 1;
}

void show_stat_info(char *fname, struct stat *buf) {
    /*
     * display info of fname
     */
    printf("    mode: %o\n", buf->st_mode);  // mode of file
    printf("  linkes: %d\n", buf->st_nlink); // number of hard links
    printf("    user: %d\n", buf->st_uid);   // User ID of the file
    printf("   group: %d\n", buf->st_gid);   // Group ID of the file
    printf("    size: %d\n", buf->st_size);  // file size, in bytes
    printf(" modtime: %d\n", buf->st_mtime);  // last data modification time
    printf("    name: %s\n", fname);         // filename
}

