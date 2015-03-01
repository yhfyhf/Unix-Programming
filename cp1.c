#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define MAXSIZE 4096

void oops(char *s1, char *s2);

int main(int argc, char *argv[]) {
    int src_fd, dest_fd;
    ssize_t num_read;
    char buf[MAXSIZE];

    if (argc != 3) {
        fprintf(stderr, "usage: %s source_file target_file\n", *argv);
        exit(1);
    }

    if ((src_fd = open(argv[1], O_RDONLY)) == -1)
        oops("Cannot open", argv[1]);       
    if ((dest_fd = creat(argv[2], 0644)) == -1)
        oops("Cannot open", argv[2]);
    while ((num_read = read(src_fd, buf, MAXSIZE)) > 0)
        if (write(dest_fd, buf, num_read) != num_read)
            oops("Write error to ", argv[2]);

    if (num_read == -1)
        oops("Read error from ", argv[1]);
    close(src_fd);
    close(dest_fd);
    
}

void oops(char *s1, char *s2) {
    fprintf(stderr, "Error: %s", s1);
    perror(s2);
    exit(1);
}
