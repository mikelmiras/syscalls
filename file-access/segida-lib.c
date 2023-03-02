#include <stdio.h> 
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
    if (argc==2) n = atoi(argv[1]);     // parametroa jaso

    FILE *fileoutput = fopen(OUTPUTFILE, "w+"); // Ireki fitxategia

    for (i=1;i<=n;i++) {                // for 1 to 'jasotako parametrora'
        fprintf(fileoutput, "%d\n", i); // idatzi beharreko testua: zenbakia + lerro_jauzia
    }
    fclose(fileoutput);                 // itxi fitxategia

    remove(OUTPUTFILE);
    return 0; 
} 
