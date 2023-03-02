#include <stdio.h> 
#include <unistd.h>
#include <fcntl.h> 
#include <stdlib.h>
#include <string.h>
#include <errno.h> 

#define MAX_DIGT_ZBK 10
#define OUTPUTFILE "emaitza.txt"

/* extern int errno;  */

int main(int argc, char *argv[]) 
{      
    int i;
    char text[MAX_DIGT_ZBK];
    int n=1;
    if (argc==2) n = atoi(argv[1]); // parametroa jaso
    // (argc==2) --> egiaztatu parametro kopurua 1 dela (programa + parametroa)
    // argv[1] --> jaso  parametroa (beti string formatuan)
    // atoi(argv[1]) --> itzuli zenbakia string formatutik zenbakira

    // Ireki fitxategia
    int fd = open(OUTPUTFILE, O_CREAT | O_WRONLY, 0600);  
    // O_CREAT: ez badago, sortu
    // O_WRONLY: idazteko irekia
    // 0600: fitxategia sortuz gero, ezarriko diren baimenak
    // azkenengo parametroa hautazkoa da (adierazi ezean, baimen lehenetsiak erabiltzen dira)
    printf("Fitxategia irekita: fd = %d\n", fd); 
      
    if (fd ==-1) {  // open-ek huts eginez gero
        printf("Errore kodea % d\n", errno); // Errore kodea
        perror("Program");    // Errorearen deskribapena
    } 

    for (i=1;i<=n;i++) {            // for 1 to 'jasotako parametrora'
        sprintf(text, "%d\n", i);   // idatzi beharreko testua: zenbakia + lerro_jauzia
        write(fd,text,strlen(text)); // idatzi sistema-deia erabiliz
        /* printf("%s",text); */    // idatzi liburutegiko funtzioa erabiliz
    }
    close(fd); // itxi fitxategia

    unlink(OUTPUTFILE);
    return 0; 
} 
