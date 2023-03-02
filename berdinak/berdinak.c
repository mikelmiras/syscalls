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
// Fitxategien izena lortu
char *fitx1 = argv[1];
char *fitx2 = argv[2];
// stat motako struct-ak definitu, fitxategien metadatuak gordetzeko
struct stat stat_fitx1;     
struct stat stat_fitx2;
// stat funtzioa bidez fitxategien metadatuak lortu eta gorde
stat(fitx1, &stat_fitx1);
stat(fitx2, &stat_fitx2);
// Fitxategien metadatuetik tamaina off_t motako aldagai batean gorde
off_t tamaina_fitx1 = stat_fitx1.st_size; 
off_t tamaina_fitx2 = stat_fitx2.st_size;

// Tamainak (bytetan) konparatu. Berdinak ez badira fitxategiak ez dira berdinak eta, hortaz, fitxategiak itxi eta 1 kodearekin atera.
if (tamaina_fitx1 != tamaina_fitx2) {
close(fd1);
close(fd2);
exit(1);
}

// Begizta bat sortu fitxategiak byte-ka konparatzeko
    while (1) {
	// Begiztaren hasieran lseek funtzioa erabiliz fitxategia irakurtzeko erakuslea birkolokatzen da, hurrengo bytak irakurtzeko.
	// Lehenengo parametroa fitxategia da (aurretik open funtzioarekin zabaldutakoa). 
	// Bigarren parametroa irakurketa posizioa da, hau da, zer bytetik aurrera irakurri nahi den.
	// SEEK_SET konstanteak esan nahi du hasieratik hasiko garela kontatzen, hau da: 0 + offset.
        offset1 = lseek(fd1, offset1, SEEK_SET);
        offset2 = lseek(fd2, offset2, SEEK_SET);
	// Lortutako balioa -1 bada, errore bat gertatu dela esan nahi du.
        if (offset1 < 0 || offset2 < 0) {
            close(fd1); 
            close(fd2);
            exit(1);
        }
	// Fitxategia irakurtzen da aurretik zehaztutako offset posizioan hasita. Kasu honetan byte-ka irakurtzen da.
	// buffer1 eta buffer2 aldagaiak char motakoak direnez, 1 byte bakarrik gorde dezakete. read funtzioak bueltatzen du zenbat byte irakurri diren.
	// Irakurri diren bytak ez badira 1, gerta daiteke fitxategi bukaerara ailegatu izatea.
        if (read(fd1, &buffer1, sizeof(buffer1)) != 1 ||
            read(fd2, &buffer2, sizeof(buffer2)) != 1) {
            break;
        }
	// bufferrean gorde da irakurritako byta. Konparatzen da eta berdina ez bada, fitxategiak ezberdinak direla esan nahi du.
        if (buffer1 != buffer2) {
            close(fd1);
            close(fd2);
            exit(1);
        }
	// offsetari +1 egiten zaio hurrengo byte-ra pasatzeko.
        offset1++;
        offset2++;
    }
	// Bukaera. Hona ailegatu bada esan nahi du fitxategiak berdinak direla. Ixten dira eta 0 kodea bueltatzen da.
    close(fd1);
    close(fd2);
    exit(0);
}

