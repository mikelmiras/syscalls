#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
    int fd1, fd2;
    char buffer1, buffer2;
    int offset1 = 0, offset2 = 0;
 	
    char* fileerr = "Fitxategia ezin da zabaldu";
    // Argumentu guztiak (2 fitxategiak) ez badira zehaztu, bueltatu
    if (argc != 3) {
        exit(1);
    }
	
    // Zabaldu 1. fitxategia
    fd1 = open(argv[1], O_RDONLY);
    // 1. fitxategia ezin bada zabaldu, bueltatu
    if (fd1 < 0) {
	write(STDERR_FILENO, fileerr, strlen(fileerr));
        exit(1);
    }
 
    // 1. fitxategiko gauza bera
    fd2 = open(argv[2], O_RDONLY);
    if (fd2 < 0) {
        close(fd1);
        exit(1);
    }

char *fitx1 = argv[1];
char *fitx2 = argv[2];
struct stat stat_fitx1;     
struct stat stat_fitx2;
stat(fitx1, &stat_fitx1);
stat(fitx2, &stat_fitx2);
off_t tamaina_fitx1 = stat_fitx1.st_size; 
off_t tamaina_fitx2 = stat_fitx2.st_size;

if (tamaina_fitx1 != tamaina_fitx2) {
close(fd1);
close(fd2);
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

