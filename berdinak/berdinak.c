#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int fd1, fd2;
    char buffer1, buffer2;
    int offset1 = 0, offset2 = 0;

    if (argc != 3) {
        exit(1);
    }

    fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0) {
        exit(1);
    }

    fd2 = open(argv[2], O_RDONLY);
    if (fd2 < 0) {
        close(fd1);
        exit(1);
    }

    while (1) {
        offset1 = lseek(fd1, offset1, SEEK_SET);
        offset2 = lseek(fd2, offset2, SEEK_SET);
        if (offset1 < 0 || offset2 < 0) {
            close(fd1);
            close(fd2);
            exit(1);
        }

        if (read(fd1, &buffer1, sizeof(buffer1)) != 1 ||
            read(fd2, &buffer2, sizeof(buffer2)) != 1) {
            break;
        }

        if (buffer1 != buffer2) {
            close(fd1);
            close(fd2);
            exit(1);
        }

        offset1++;
        offset2++;
    }

    close(fd1);
    close(fd2);
    exit(0);
}

